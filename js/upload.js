new_element = document.createElement('script')
new_element.setAttribute('type', 'text/javascript')
new_element.setAttribute('src', 'jQuery1.11.3.min.js')
document.body.appendChild(new_element)

const $contentType = 'image/jpg'
const $token = ''
const $fileName = 'phone.jpg'
const $url = 'https://api-ap-seoul-1.getway.sinso.io'
const $data = '@/C:/Users/HASEE/Desktop/phone.jpg'
function upload($contentType, $token, $fileName, $url, $data) {
  $.ajax({
    url: `${$url}/v1/upload?name=${$fileName}`,
    type: 'POST',
    dataType: 'json',
    headers: {
      Token: $token,
      'Content-Type': $contentType,
    },
    data: $data,
    success: (res) => {
      if (res.code == 200) {
        console.log(res)
      }
    },
  })
}
