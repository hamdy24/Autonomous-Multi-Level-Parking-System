import socket

HOST = '0.0.0.0'
PORT = 8001

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("Server is listening on port", PORT)
    conn, addr = s.accept()
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            print("Received data:", data.decode())
            # Send bytes back to client
            conn.sendall(b"Hello from server!")
