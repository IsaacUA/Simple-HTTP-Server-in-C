# Simple HTTP Server in C

This project is a basic HTTP server implemented in C. It serves a specified `index.html` file over a user-defined port.

## Features

- 📁 Accepts custom paths to `index.html`
- 🔢 Supports configurable port numbers
- 📤 Sends HTTP responses with the provided HTML content

## Prerequisites

Ensure your system has:

- 🛠️ GCC (or any C compiler)
- 💻 Linux/macOS environment (or WSL on Windows)

## Compilation

To compile the server, use the following command:

```bash
gcc server.c -o server
```

## Usage

1. ▶️ Run the server:

```bash
./server
```

2. 📂 Provide the path to your `index.html` and the port number:

```
Path to index.html:
> /path/to/index.html

Port:
> 8080
```

3. 🌐 Access the server at:

```
http://localhost:8080
```

## Example

1. 📄 Create a simple `index.html` file:

```html
<!DOCTYPE html>
<html>
  <head>
    <title>My HTTP Server</title>
  </head>
  <body>
    <h1>Welcome to My HTTP Server!</h1>
  </body>
</html>
```

2. 🚀 Start the server and provide the path:

```bash
./server
Path to index.html:
> index.html

Port:
> 8080
```

3. 🌍 Open a browser and visit:

```
http://localhost:8080
```

## Notes

- 📡 The server only handles basic GET requests.
- 📏 The buffer size is limited to 4096 bytes.

## License

📜 This project is licensed under the MIT License.
