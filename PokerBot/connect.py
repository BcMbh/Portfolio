import requests

USERNAME = 'gameserver042'
PASSWORD = 'twdAW66symaZ'


#Register players
def register_player(name):
    url = f'https://gametheorychallenge.tesserac.ai/api/player/register'
    payload = {
        "display_name": name
    }

    response = requests.post(url, json=payload, auth=(USERNAME, PASSWORD))
    if response.status_code == 200:
        print(f"Registered '{name}'")
    else:
        print(f"Failed '{name}':", response.status_code, response.text)

for i in range(1, 4):
    register_player(f"PokerBot{i}")

#Start tournament
def start_tournament():
    url = f'https://gametheorychallenge.tesserac.ai/api/admin/tournament/start'
    response = requests.post(url, auth=(USERNAME, PASSWORD))
    
    if response.status_code == 200:
        print("Tournament started:", response.json())
    else:
        print("Failed to start:", response.status_code, response.text)