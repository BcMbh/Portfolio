import requests

username = "gameserver042"
password = "twdAW66symaZ"
AUTH = (username, password)

# Shorctcut function
def make_request(method, url, payload=None):
    try:
        method = method.upper()
        if method == 'GET':
            response = requests.get(url, auth=AUTH)
        elif method == 'POST':
            response = requests.post(url, json=payload, auth=AUTH)
        elif method == 'DELETE':
            response = requests.delete(url, auth=AUTH)
        else:
            raise ValueError(f"Unsupported HTTP method: {method}")

        if response.status_code == 200:
            return response.json()
        else:
            print(f"API Error [{response.status_code}]: {response.text}")
            return None

    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}")
        return None

# Admin
def get_tournament_state():
    data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/state')
    return data.get("tournament_state") if data else None


def admin_get_player_list():
    data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/players')
    if data:
        print("Player List:")
        for player in data:
            print(f" - {player}")
    return data


def register_player(name):
    payload = {"display_name": name}
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/register', payload)
    if data:
        print(f"Registered '{name}':", data)
    return data


def start_tournament():
    make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/start')
    print("Tournament started.")


def stop_tournament():
    make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/stop')
    print("Tournament stopped.")


def pause_tournament():
    make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/pause')
    print("Tournament paused.")


def resume_tournament():
    make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/resume')
    print("Tournament resumed.")


def restart_tournament():
    confirm = input("Are you sure you want to restart the tournament? (Y/N): ").lower()
    if confirm == "y":
        make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/restart')
        print("Tournament restarted.")


def eliminate_player(player_id):
    make_request('DELETE', f'admin/players/{player_id}')
    print(f"Player {player_id} eliminated.")


def get_active_games():
    data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/games')
    if data:
        print("Active Games:", data)
    return data


# Terminal UI
def show_control_panel():
    while True:
        state = get_tournament_state()
        print("Tournament State:", state)
        print("Admin Control Panel:")
        print("1. Start/Stop Tournament")
        print("2. Pause/Resume Tournament")
        print("3. Restart Tournament")
        print("4. Register Player")
        print("5. Eliminate Player")
        print("6. Get Player List")
        print("7. Get Tournament State")
        print("8. Get Active Games")
        print("9. Exit Control Panel \n")
        action = input("Enter the code: ")

        match action:
            case "1": # Start/Stop Tournament
                if state in ("registration", "finished"):
                    start_tournament()
                else:
                    stop_tournament()
            case "2": # Pause/Resume Tournament
                if state == "paused":
                    resume_tournament()
                else:
                    pause_tournament()
            case "3": # Restart Tournament
                restart_tournament()
            case "4": # Register Player
                player_name = input("Enter player name (Enter 'Cancel' to go back): ").strip()
                if player_name and player_name.lower() != "cancel":
                    register_player(player_name)
            case "5": # Eliminate Player
                pid = input("Insert player_id to eliminate: ").strip()
                if pid:
                    eliminate_player(pid)
            case "6": # Get Player List
                admin_get_player_list()
            case "7": # Get Tournament State
                print(get_tournament_state())
            case "8": # Get Active Games
                get_active_games()
            case "9": # Exit Control Panel
                print("Exited the control panel successfully")
                break
            case _:
                print("Invalid choice, try again.")
show_control_panel()


#Bot/Player
def check_tournament_phase():
    data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/player/tournament/phase')
    return data.get("tournament_state") if data else None


def register_self(name):
    phase = check_tournament_phase()
    if phase == "registration":
        payload = {"display_name": name}
        data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/register', payload)
        if data:
            print(f"Registered '{name}'", data)
        return data
    else:
        print("The tournament is not open to registration right now")
        return None


def wait_for_tournament_start():
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/wait-for-tournament-start')
    if data:
        print("Waiting for tournament start")
    return data


# In control_panel.py

def wait_for_turn(player_id):
    payload = {"player_id": player_id}
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/wait-until-turn', payload)

    if not data:
        return None
    if data.get("is_your_turn"):
        print(f"It's your turn! Game {data['game_id']}, Hand {data['current_hand']}")
        return data
    else:
        return None


def player_action(player_id, action, amount=None):
    payload = {'player_id': player_id, 'action': action}
    if amount is not None:
        payload['amount'] = amount
    data = make_request('POST', 'https://gameserver042.poker.tesserac.ai/api/player/action', payload)
    if data:
        print("Action successfully submitted", data)
    return data


def player_get_list():
    data = make_request('GET', 'https://gameserver042.poker.tesserac.ai/api/player/list')
    if data:
        print(data)
    return data


def get_player_state(player_id):
    data = make_request('GET', f'https://gameserver042.poker.tesserac.ai/api/player/{player_id}/state')
    if data:
        print(data)
    return data
