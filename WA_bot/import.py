import pywhatkit as kit
import time
import random

def send_messages_and_picture(contact_list, message1, message2, picture_path, interval_minutes=2):
    for contact in contact_list:
        try:
            # Send the first message
            kit.sendwhatmsg_instantly(contact, message1, wait_time=15)
            print(f"Sent message1 to {contact}")
            time.sleep(random.randint(1, 5))

            # Send the second message
            kit.sendwhatmsg_instantly(contact, message2, wait_time=15)
            print(f"Sent message2 to {contact}")
            time.sleep(random.randint(1, 5))

            # Send the image
            kit.sendwhats_image(contact, picture_path, "test")
            print(f"Sent image to {contact}")
            time.sleep(interval_minutes * 2)  

        except Exception as e:
            print(f"Error with contact {contact}: {e}")

    
contacts = ["+1000002", "+100001"] 

# message and image
message1 = "."
message2 = ""
picture_path = r"C:\"

# Run it
send_messages_and_picture(contacts, message1, message2, picture_path, interval_minutes=1)
