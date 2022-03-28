import requests
import os

GATEWAY = "https://api-ap-seoul-1.getway.sinso.io"
URL = "/v1/upload"
CONTENT_TYPE = "image/jpg"
FILE_PATH = ""
FILENAME = "1.jpg"
TOKEN = ""


def upload(url, token, content_type, file):
    headers = {
        "Content-Type": content_type,
        "Token": token
    }
    params = {
        "name": FILENAME
    }
    response = requests.post(url=url, data=file, headers=headers, params=params)
    print(response.text)


if __name__ == '__main__':
    f = open(os.path.join(FILE_PATH, FILENAME), "rb")
    upload(GATEWAY+URL, TOKEN, CONTENT_TYPE, f)
