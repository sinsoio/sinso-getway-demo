package main

import (
	"bytes"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"net/http"
)

func main() {
	token := ""
	fileName := "1.jpg"
	fileDir := "./php/"
	contentType := "image/jpg"
	body, err := ioutil.ReadFile(fileDir + fileName)
	if err != nil {
		fmt.Println(err)
		return
	}
	gateway := "https://api-ap-seoul-1.getway.sinso.io"
	url := gateway + "/v1/upload?name=" + fileName
	uploadSuccess, err := upload(token, contentType, url, body)
	if err != nil {
		fmt.Println(err)
		return
	}
	fmt.Println(uploadSuccess)
}

type Response struct {
	Ts        int64         `json:"ts"`
	Code      int           `json:"code"`
	ErrorCode int           `json:"error_code"`
	Message   string        `json:"message"`
	Data      UploadSuccess `json:"data"`
}

type UploadSuccess struct {
	Gateway   string `json:"gateway"`
	Url       string `json:"url"`
	Reference string `json:"reference"`
}

func upload(token string, contentType string, url string, body []byte) (*Response, error) {
	client := http.Client{}
	req, err := http.NewRequest(http.MethodPost, url, bytes.NewBuffer(body))
	if err != nil {
		return nil, err
	}
	req.Header.Set("Token", token)
	req.Header.Set("Content-Type", contentType)
	response, err := client.Do(req)
	if err != nil {
		return nil, err
	}
	if response.StatusCode != http.StatusOK {
		return nil, errors.New("upload failed")
	}
	defer response.Body.Close()
	var uploadSuccess *Response
	if body, err := ioutil.ReadAll(response.Body); err != nil {
		return nil, err
	} else {
		if err := json.Unmarshal(body, &uploadSuccess); err != nil {
			return nil, err
		}
	}
	return uploadSuccess, nil
}
