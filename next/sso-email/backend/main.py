from fastapi import FastAPI, Request
from dotenv import load_dotenv
import smtplib
import ssl
import os


# read environment variables
load_dotenv()

email = os.environ["SERVER_GMAIL_ADDRESS"]
app_passwd = os.environ["SERVER_GMAIL_APP_PASSWD"]

context = ssl.create_default_context()

message = """\
Subject: Hello from python

This message is sent from Python!

Best,
Broccoli Test
"""

with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context) as server:
    server.login(email, app_passwd)
    server.sendmail(email, "broccolitest524+client@gmail.com", message)

app = FastAPI(title="sso-email backend")


@app.post("/send_email")
async def send_email(request: Request):
    data = await request.json()
    print(f"{data['user_name']} | {data['user_email']}")
    print("--Function end--")
