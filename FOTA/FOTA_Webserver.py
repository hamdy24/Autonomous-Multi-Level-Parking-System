from flask import Flask, request, redirect, url_for, send_from_directory
import os

app = Flask(__name__)

# Hardcoded admin credentials (for demo purposes)
ADMIN_USERNAME = 'ADMIN_2024'
ADMIN_PASSWORD = 'ADMIN_2024'

# Determine the directory of the current script
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
UPLOAD_FOLDER = SCRIPT_DIR  # Set upload folder to the script directory
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# HTML template for login form and file upload
login_template = '''
<!doctype html>
<html>
<head>
    <title>Login</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: url('/background.jpg') no-repeat center center fixed;
            background-size: 1700px 850px;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        .container {
            background-color: rgba(255, 255, 255, 0.8);
            padding: 20px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            text-align: center;
        }
        h1 {
            color: #333;
        }
        input[type="text"], input[type="password"] {
            margin: 10px 0;
            padding: 8px;
            width: 200px;
            border-radius: 4px;
            border: 1px solid #ccc;
        }
        input[type="submit"] {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Login</h1>
        <form method="post" action="/login">
            <input type="text" name="username" placeholder="Username"><br>
            <input type="password" name="password" placeholder="Password"><br>
            <input type="submit" value="Login">
        </form>
    </div>
</body>
</html>
'''

# Route for login page
@app.route('/')
def login():
    return login_template

# Route for handling login form submission
@app.route('/login', methods=['POST'])
def login_user():
    username = request.form['username']
    password = request.form['password']
    
    if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
        # If login successful, redirect to upload page
        return redirect(url_for('upload_file_form'))
    else:
        # If login fails, redirect back to login page
        return redirect(url_for('login'))

# Route for serving background image
@app.route('/background.jpg')
def background_image():
    return send_from_directory(SCRIPT_DIR, 'background.jpg')

# Route for displaying file upload form (accessible only after login)
@app.route('/upload', methods=['GET', 'POST'])
def upload_file_form():
    if request.method == 'GET':
        return '''
        <!doctype html>
        <html>
        <head>
            <title>Upload New File</title>
            <style>
                body {
                    font-family: Arial, sans-serif;
                    background: url('/background.jpg') no-repeat center center fixed;
                    background-size: 1700px 850px;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    height: 100vh;
                    margin: 0;
                }
                .container {
                    background-color: rgba(255, 255, 255, 0.8);
                    padding: 20px;
                    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                    border-radius: 8px;
                    text-align: center;
                }
                h1 {
                    color: #333;
                }
                input[type="file"] {
                    margin: 20px 0;
                }
                input[type="submit"] {
                    background-color: #4CAF50;
                    color: white;
                    padding: 10px 20px;
                    border: none;
                    border-radius: 4px;
                    cursor: pointer;
                }
                input[type="submit"]:hover {
                    background-color: #45a049;
                }
            </style>
        </head>
        <body>
            <div class="container">
                <h1>Upload New File</h1>
                <form method="post" enctype="multipart/form-data">
                    <input type="file" name="file"><br>
                    <input type="submit" value="Upload">
                </form>
            </div>
        </body>
        </html>
        '''
    elif request.method == 'POST':
        if 'file' not in request.files:
            return redirect(request.url)
        
        file = request.files['file']
        if file.filename == '':
            return redirect(request.url)

        if file:
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], 'TestBootloader.bin')
            file.save(filepath)
            return '''
            <!doctype html>
            <html>
            <head>
                <title>File Uploaded</title>
                <style>
                    body {{
                        font-family: Arial, sans-serif;
                        background: url('/background.jpg') no-repeat center center fixed;
                        background-size: 1700px 850px;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                        height: 100vh;
                        margin: 0;
                    }}
                    .container {{
                        background-color: rgba(255, 255, 255, 0.8);
                        padding: 20px;
                        box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
                        border-radius: 8px;
                        text-align: center;
                    }}
                    h1 {{
                        color: #333;
                    }}
                    a {{
                        display: inline-block;
                        margin-top: 20px;
                        text-decoration: none;
                        background-color: #4CAF50;
                        color: white;
                        padding: 10px 20px;
                        border-radius: 4px;
                    }}
                    a:hover {{
                        background-color: #45a049;
                    }}
                </style>
            </head>
            <body>
                <div class="container">
                    <h1>File Uploaded Successfully</h1>
                    <p>Saved to: {filepath}</p>
                    <a href="/upload">Upload Another File</a>
                </div>
            </body>
            </html>
            '''.format(filepath=filepath)

if __name__ == '__main__':
    app.run(port=5000)
