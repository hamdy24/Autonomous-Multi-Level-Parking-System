import socket

def send_tcp_message(message):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 81))
    client_socket.send(message.encode())
    
    # Receive the server's response
    response = client_socket.recv(1024)
    print(f'Response from server: {response.decode()}')
    
    client_socket.close()

if __name__ == '__main__':
    message = "Hello, TCP Server!"
    send_tcp_message(message)