import time
import sys
from control_panel import make_request
from texas_holdem_poker import hand_rank
from texas_holdem_poker.poker_card import Card

#Bot available actions
def register_self(name):
    phase_data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/player/tournament/phase')
    if phase_data and phase_data.get('tournament_state') == 'registration':
        payload = {"display_name": name}
        data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/register', payload)
        if data:
            print(f"Registered as {name}: {data}")
            return data.get("player_id")
    else:
        print("Registration phase closed.")
    return None


def wait_for_tournament_start():
    print("Waiting for tournament start...")
    make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/wait-for-tournament-start')
    print("Tournament started!")


def wait_for_turn(player_id):
    payload = {"player_id": player_id}
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/wait-until-turn', payload)
    if not data:
        return None

    if data.get("is_your_turn"):
        print(f"It's your turn! Game {data['game_id']}, Hand {data['current_hand']}")
        return data
    else:
        print("Still waiting for turn...")
        return None


def player_action(player_id, action, amount=None):
    payload = {"player_id": player_id, "action": action}
    if amount is not None:
        payload["amount"] = amount
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/action', payload)
    if data:
        print(f"Action submitted: {action} {amount if amount else ''}")
    else:
        print("Failed to submit action.")

def hand_eval(cards):
    print("=== DEBUG hand_eval ===")
    print("Input cards:", cards)

    hand = []
    flush_draw = False
    suit_counts = {}
    
    for card_data in cards:
        rank = card_data['rank']
        suit = card_data['suit']

        #print(f"Processing card: suit='{suit}', rank='{rank}'")
        
        # Convert numeric rank to string
        if 2 <= rank <= 9:
            rank = str(rank)

        rank_map = {
            14: 'A', 13: 'K', 12: 'Q', 11: 'J', 10: 'T'
        }
        if rank in rank_map:
            rank = rank_map[rank]
        
        # if suit not in Card.SUITS:
        #     print(f"ERROR: Invalid suit '{suit}'. Valid suits are: {Card.SUITS}")
        # if rank not in Card.RANKS + Card.ILLUSION_RANKS:
        #     print(f"ERROR: Invalid rank '{rank}'. Valid ranks are: {Card.RANKS}")

        hand.append(Card(suit, rank))
        # Count suits to check for flush draws
        suit_counts[suit] = suit_counts.get(suit, 0) + 1
    
    # Evaluate the hand using import
    hand_score = hand_rank.HandRankCheck.check(hand)

    hand_val = hand_score.hand_rank

    if hand_val.value < hand_rank.HandRank.FLUSH.value:
        flush_draw = any(count == 4 for count in suit_counts.values())

    return hand_score, hand, flush_draw, suit_counts

def available_actions(all_pbets, pchips, pid):
    avail_actions = ['fold', 'all_in']
    
    if all_pbets:
        max_bets = max(all_pbets.values())
    else:
        max_bets = 0

    pbet = all_pbets.get(pid, 0)
    call_amount = max_bets - pbet

    # Check to see if check action is available
    if call_amount == 0:
        avail_actions.append('check')
    
    # Check to see if call action is available
    if call_amount > 0 and pchips >= call_amount:
        avail_actions.append('call')
    
    # Check to see if bet/raise action is available
    if pchips > 0:
        if max_bets == 0:
            avail_actions.append('bet')
        elif pchips > call_amount:
            avail_actions.append('raise')

    return avail_actions, max_bets, call_amount

def big_small_bet_raise(avail_actions, max_bet, pchips, pot_total, bbet, sbet):
    if 'bet' in avail_actions: # If can bet
        if pchips > bbet * pot_total: # If can bet half the pot
            return {'action': 'bet', 'amount': bbet * pot_total}
        elif pchips > sbet * pot_total:
            return {'action': 'bet', 'amount': sbet * pot_total}
        else:
            call_check_fold(avail_actions, max_bet)
    elif 'raise' in avail_actions: # If can raise
        if pchips > (max_bet + bbet * pot_total):# If can raise half the pot
            return {'action': 'raise', 'amount': bbet * pot_total}
        elif pchips > max_bet + sbet * pot_total:
            return {'action': 'raise', 'amount': sbet * pot_total}
        else:
            call_check_fold(avail_actions, max_bet)
    else:
        call_check_fold(avail_actions, max_bet)

def call_check_fold(avail_actions, max_bet):
    if 'call' in avail_actions:
        return {'action': 'call', 'amount': max_bet}
    check_fold(avail_actions)
    
def check_fold(avail_actions):
    if 'check' in avail_actions:
        return {'action': 'check'}
    else:
        return {'action': 'fold'}

def decide_action(hand_type, hand, flush_draw, avail_actions, suit_counts, current_round, max_bet, pot_total, pchips, call_amount):
    print(f"Round: {current_round}")
    print(f"Hand: {hand_type.hand_rank.name} (value: {hand_type.hand_rank.value})")
    print(f"Flush draw: {flush_draw}")
    print(f"Available actions: {avail_actions}")
    print(f"Suit counts: {suit_counts}")
    print(f"Max bet: {max_bet}, Pot: {pot_total}, Chips: {pchips}")
    match current_round:
    # Pre-flop
        case 1:
            ranks = [card.rank for card in hand] # Get ranks from Card
            # If hole cards are high card
            if hand_type.hand_rank.value <1:
                # If hole cards are not suited
                if any(count < 2 for count in suit_counts.values()):
                    return check_fold(avail_actions)
                elif any(rank >= 10 for rank in ranks): # If hole cards are suited and one of the hole cards are ten or higher
                    return call_check_fold(avail_actions, max_bet)
                else:
                    return check_fold(avail_actions)

            else: # If hole cards are suited
                if any(rank >= 9 for rank in ranks): # If suited cards are 9 or higher
                    return big_small_bet_raise(avail_actions, max_bet, pchips, pot_total, 0.25, 0.15)

    # Flop
        case 2:
            ranks = [card.rank for card in hand] # Get ranks from Card
            # If hand is high card
            if hand_type.hand_rank.value <1:
                # If hand is a flush draw and to call is less than or equal to 1/3 of current chip amount
                if flush_draw and max_bet <= 0.25 * pchips:
                    return call_check_fold(avail_actions, max_bet)
                else:
                    return check_fold(avail_actions)

            # If hand is pair
            elif hand_type.hand_rank.value == 1:
                if flush_draw and max_bet <= 0.35 * pchips:
                    return call_check_fold(avail_actions, max_bet)
                else:
                    return check_fold(avail_actions)

            # If hand is Two Pairs
            elif hand_type.hand_rank.value == 2:
                if max(rank >= 4 for rank in ranks):
                    return big_small_bet_raise(avail_actions, max_bet, pchips, pot_total, 0.35, 0.2)
                else:
                    return call_check_fold(avail_actions, max_bet)
            
            # If hand is Three of a Kind
            elif hand_type.hand_rank.value == 3:
                return big_small_bet_raise(avail_actions, max_bet, pchips, pot_total, 0.4, 0.25)
            
            # If hand is Straight or better
            else:
                return big_small_bet_raise(avail_actions, max_bet, pchips, pot_total, 0.5, 0.2)

    #Turn
        case _:
            return {'action': 'fold'}
        
                




def bot_main(name):
    player_id = register_self(name)
    if not player_id:
        print("Failed to register. Exiting.")
        return

    wait_for_tournament_start()

    while True:
        phase_data = make_request('GET', f'https://gameserver042.poker.tesserac.ai/api/player/tournament/phase')
        state = phase_data.get("tournament_state") if phase_data else None

        if state in ["paused", "pause_pending"]:
            print("Tournament paused. Waiting...")
            time.sleep(5)
            continue
        elif state == "finished":
            print("Tournament finished.")
            break

        turn_data = wait_for_turn(player_id)
        if not turn_data:
            continue

        cards = turn_data['player_info']['hand']['cards']
        hand_type, hand, flush_draw, suit_counts = hand_eval(cards)
        avail_actions, max_bet, call_amount = available_actions(turn_data['player_bets'], turn_data['player_info']['chips'], player_id)

        action = decide_action(hand_type, hand, flush_draw, avail_actions, suit_counts, turn_data['current_round'], max_bet, turn_data['pot_total'], turn_data['player_info']['chips'], call_amount)
        player_action(player_id, action["action"], action.get("amount"))


if __name__ == "__main__":
    if len(sys.argv) > 1:
        bot_name = sys.argv[1]
    else:
        bot_name = "PokerBot"
    bot_main(bot_name)
        

