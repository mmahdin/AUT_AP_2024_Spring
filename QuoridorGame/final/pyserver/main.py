import socket
import json


def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(2)

    clients = []

    while len(clients) < 2:
        client_socket, addr = server_socket.accept()
        print(f"Connected to {addr}")
        clients.append(client_socket)

    while True:
        for i in range(2):
            data = b''
            while True:
                chunk = clients[i].recv(1024)
                if not chunk:
                    break
                data += chunk
                if b'\n' in chunk:  # Assuming messages are terminated by a newline
                    break

            data = data.decode('utf-8').strip()
            if not data:
                break

            try:
                json_data = json.loads(data)
                response_data = json.dumps(json_data) + '\n'
                clients[1 - i].send(response_data.encode('utf-8'))
                print(f"Sent to client {2-i}: {response_data}\n\n")
            except json.JSONDecodeError as e:
                print(f"JSON decode error: {e}")


if __name__ == "__main__":
    start_server('localhost', 60011)
