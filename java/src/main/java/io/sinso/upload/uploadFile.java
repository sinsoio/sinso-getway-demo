package io.sinso.upload;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;

public class uploadFile {

    public static void main(String[] args) {
        System.out.println(upload());
    }

    public static String upload() {
        try {
            String filePath = "io/sinso/upload/1.jpg";
            File file = new File(filePath);
            URL url = new URL("https://api-ap-seoul-1.getway.sinso.io/v1/upload?name=1.jpg");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            //Please enter your token
            conn.setRequestProperty("Token", "");
            conn.setRequestProperty("Content-type", "application/x-www-form-urlencoded");
            conn.setDoOutput(true);
            conn.setDoInput(true);
            conn.setChunkedStreamingMode(1024 * 1024);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("connection", "Keep-Alive");
            conn.setRequestProperty("Charsert", "UTF-8");
            conn.setConnectTimeout(50000);
            conn.connect();
            OutputStream out = new DataOutputStream(conn.getOutputStream());
            DataInputStream in = new DataInputStream(new FileInputStream(file));
            int bytes = 0;
            byte[] bufferOut = new byte[2048];
            while ((bytes = in.read(bufferOut)) != -1) {
                out.write(bufferOut, 0, bytes);
            }
            in.close();

            out.flush();
            out.close();
            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            String line = null;
            while ((line = reader.readLine()) != null) {
                return line;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
}
