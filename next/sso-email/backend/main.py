from fastapi import FastAPI, Request
from dotenv import load_dotenv
import smtplib
import ssl
import os
from typing import Tuple
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart


app = FastAPI(title="sso-email backend")


def get_server_gmail_credentials() -> Tuple[str, str]:
    load_dotenv()
    email = os.environ["SERVER_GMAIL_ADDRESS"]
    app_passwd = os.environ["SERVER_GMAIL_APP_PASSWD"]
    return (email, app_passwd)


def get_email_message(receiver_name: str) -> Tuple[str, str]:
    text = f"""\
Hi {receiver_name}, 
This email is from python with plaintext!

Thanks,
Tester
"""

    html = f"""\
<html>
    <body>
        <p>
            Hi {receiver_name}, <br>
            This is a message from python with html!! <br>
            Book a hotel with this link: 
            <a href="http://localhost:3000/">Book now</a> <br>
            <br>
            Thanks, <br>
            Tester <br>
        </p>
    </body>
</html>
"""

    return (text, html)


def send_test_email(
    sender_email: str, app_passwd: str, receiver_name: str, receiver_email: str
) -> None:
    message = MIMEMultipart("alternative")
    message["Subject"] = "Python Email"
    message["From"] = sender_email
    message["To"] = receiver_email

    text, html = get_email_message(receiver_name)
    part1 = MIMEText(text, "plain")
    part2 = MIMEText(html, "html")

    message.attach(part1)
    message.attach(part2)

    context = ssl.create_default_context()
    with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context) as server:
        server.login(sender_email, app_passwd)
        server.sendmail(sender_email, receiver_email, message.as_string())


@app.post("/send_email")
async def send_email(request: Request) -> None:
    sender_email, app_passwd = get_server_gmail_credentials()

    data = await request.json()
    receiver_name, receiver_email = data["user_name"], data["user_email"]
    send_test_email(
        sender_email=sender_email,
        app_passwd=app_passwd,
        receiver_name=receiver_name,
        receiver_email=receiver_email,
    )
    print(f"-- Email sent to: {receiver_email} --")
