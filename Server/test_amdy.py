import requests

# Replace these variables with your actual API endpoint and parameters
api_url = 'http://localhost/my-api/amdy.php'
action = 'update_robot'
robot1_state = 121  # Replace with the desired value
robot2_state = 21  # Replace with the desired value
version = 3  # Replace with the desired value

# Define the POST parameters
params = {
    'action': action,
    'robot1_state': robot1_state,
    'robot2_state': robot2_state,
    'version': version
}

params2 = {
    'action': 'get_data'
}
# Send the POST request
response = requests.post(api_url, data=params)
response2 = requests.post(api_url, data=params2)
# Print the response
print("Response:")
print(response.text)
print("Response2:")
print(response2.text)
