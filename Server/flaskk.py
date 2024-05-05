 
from flask import Flask
import socket

app = Flask(__name__)

@app.route('/')
def hello():
    return 'Hello, World!'

def tcp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 81))
    server_socket.listen(1)
    print('TCP server listening on port 81')
    
    while True:
        client_socket, addr = server_socket.accept()
        print(f'Connection from {addr}')
        data = client_socket.recv(1024)
        print(f'Received data: {data.decode()}')
        
        response = 'Message received!'
        client_socket.send(response.encode())
        client_socket.close()

if __name__ == '__main__':
    import threading
    tcp_thread = threading.Thread(target=tcp_server)
    tcp_thread.start()
    app.run()