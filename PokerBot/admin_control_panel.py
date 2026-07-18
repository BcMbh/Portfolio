import requests
import bot_logic

username = "gameserver042"
password = "twdAW66symaZ"
response = None
tournament_state = None
player_id = None

def get_tournament_state():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/state'

    response = requests.get(url, auth=(username, password))

    if response.status_code == 200:
        data = response.json()
        return data["tournament_state"]
    else:
        print(f"Failed to get tournament state", response.status_code, response.text)

def fetch_tournament_state():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/state'

    response = requests.get(url, auth=(username, password))

    if response.status_code == 200:
        print(response.json())
    else:
        print(f"Failed to get tournament state", response.status_code, response.text)

def get_player_list():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/players'

    response = requests.get(url, auth=(username, password))

    if response.status_code == 200:
        print(response.json())
    else:
        print(f"Failed to get tournament state", response.status_code, response.text)

#Register players
def register_player(name):
    url = f'https://gameserver042.poker.tesserac.ai/api/player/register'
    payload = {
        "display_name": name
    }

    response = requests.post(url, json=payload, auth=(username, password))
    if response.status_code == 200:
        print(f"Registered '{name}'", response.json())
    else:
        print(f"Failed '{name}':", response.status_code, response.text)

# for i in range(1, 4):
#     register_player(f"PokerBot{i}")

#Start tournament
def start_tournament():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/start'
    response = requests.post(url, auth=(username, password))
    
    if response.status_code == 200:
        print("Tournament started:", response.json())
    else:
        print("Failed to start:", response.status_code, response.text)

def stop_tournament():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/stop'
    response = requests.post(url, auth=(username, password))

    if response.status_code == 200:
        print("Tournament stopped:", response.json())
    else:
        print("Failed to stop:", response.status_code, response.text)

def pause_tournament():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/pause'
    response = requests.post(url, auth=(username, password))

    if response.status_code == 200:
        print("Tournament paused: ", response.json())
    else:
        print(f"Failed to pause:", response.status_code, response.text)

def resume_tournament():
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/resume'
    response = requests.post(url, auth=(username, password))

    if response.status_code == 200:
        print("Tournament resumed: ", response.json())
    else:
        print(f"Failed to resume:", response.status_code, response.text)

def restart_tournament():
    check = input("Are you sure you want to restart the tournament? (Y/N): ")

    if check == "Y":
        url = f'https://gameserver042.poker.tesserac.ai/api/admin/tournament/restart'
        response = requests.post(url, auth=(username, password))

        if response.status_code == 200:
            print("Tournament restarted: ", response.json())
        else:
            print(f"Failed to restart:", response.status_code, response.text)
    else:
        show_control_panel()

def eliminate_player(player_id):
    url = f'https://gameserver042.poker.tesserac.ai/api/admin/players/{player_id}'

    response = requests.delete(url, auth=(username, password))
    if response.status_code == 200:
        print(response.json())
    else:
        print(response.status_code, response.text)

def get_active_games():
    url = 'https://gameserver042.poker.tesserac.ai/api/admin/tournament/games'

    response = requests.get(url, auth=(username, password))
    if response.status_code == 200:
        print(response.json())
    else:
        print(response.status_code, response.text)

def show_control_panel():
    tournament_state = get_tournament_state()
    print("Tournament State:", tournament_state)

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

    if int(action) == 1:
        if tournament_state == "registration" or tournament_state == "finished":
            start_tournament()
        else:
            stop_tournament()
        show_control_panel()

    elif int(action) == 2:
        if tournament_state == "paused":
            resume_tournament()
        else:
            pause_tournament()
        show_control_panel()    

    elif int(action) == 3:
        restart_tournament()
        show_control_panel()

    elif int(action) == 4:
        player_name = str(input("Enter player name (Enter 'Cancel' to go back): "))
        if player_name != "Cancel":
            register_player(player_name)
        show_control_panel()
    elif int(action) == 5:
        player_id = input('Insert player_id to eliminate: ')
        eliminate_player(player_id)
        show_control_panel()
    elif int(action) == 6:
        get_player_list()
        show_control_panel()
    elif int(action) == 7:
        fetch_tournament_state()
        show_control_panel()
    elif int(action) == 8:
        get_active_games()
        show_control_panel()
    else:
        print("Exited the control panel succesfully")

show_control_panel()


#Bot/Player calls ###################################################### 

def check_tournament_phase():
    url=f'https://gameserver042.poker.tesserac.ai/api/player/tournament/phase'
    response = requests.get(url, auth=(username, password))

    if response.status_code == 200:
        data = response.json()
        print(data)
        return data["tournament_state"]
    else:
        print(f"Failed to get tournament phase", response.status_code, response.text)

def register_self(name):
    tournament_phase = check_tournament_phase()
    if tournament_phase == "registration":
        url = f'https://gameserver042.poker.tesserac.ai/api/player/register'
        payload = {
            "display_name": name
        }

        response = requests.post(url, json=payload, auth=(username, password))
        if response.status_code == 200:
            data = response.json()
            print(f"Registered '{name}'", data)
        else:
            print(f"Failed '{name}':", response.status_code, response.text)
    else:
        print("The tournament is not open to registration right now")

def wait_for_tournament_start():
    url =f'https://gameserver042.poker.tesserac.ai/api/player/wait-for-tournament-start'
    
    response = requests.post(url, auth=(username, password))
    if response.status_code == 200:
        print("Waiting for tournament start")
    else:
        print("API Fail", response.status_code, response.text)

def wait_for_turn(player_id):
    url =f'https://gameserver042.poker.tesserac.ai/api/player/wait-until-turn'
    payload = {
        'player_id': player_id
    }

    response = requests.post(url, json=payload, auth=(username, password))
    if response.status_code == 200:
        print(response.json)
    else:
        print("API Fail", response.status_code, response.text)

def player_action(player_id, action, amount=None):
    url =f'https://gameserver042.poker.tesserac.ai/api/player/action'

    if amount != None:
        payload = {
            'player_id': player_id,
            'action' : action,
            'amount' : amount
        }
    else:
        payload = {
            'player_id': player_id,
            'action' : action,
        }
    
    response = requests.post(url, json=payload, auth=(username, password))
    if response.status_code == 200:
        print("Action successfully submitted", response.json())
    else:
        print("Failed to submit action", response.status_code, response.text)

def get_player_list():
    url = 'https://gameserver042.poker.tesserac.ai/api/player/list'

    response = requests.get(url, auth=(username, password))
    if response.status_code == 200:
        print(response.json())
    else:
        print("Failed to get list", response.status_code, response.text)

def get_player_state(player_id):
    url =f'https://gameserver042.poker.tesserac.ai/api/player/{player_id}/state'

    response = requests.get(url, auth=(username, password))
    if response.status_code == 200:
        print(response.json())
    else:
        print("Failed to get player state", response.status_code, response.text)