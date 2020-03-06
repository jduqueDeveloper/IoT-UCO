package co.com.luis.iot.hourserver.services.request_http;

import org.springframework.stereotype.Service;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

@Service
public class RequestHttpGetServicesImpl implements RequestHttpGetServices {

    @Override
    public String requestHttpGet(String urlRequest) throws Exception{
        StringBuilder resultado = new StringBuilder();
        URL url = new URL(urlRequest);
        HttpURLConnection conexion = (HttpURLConnection) url.openConnection();
        conexion.setRequestMethod("GET");
        BufferedReader rd = new BufferedReader(new InputStreamReader(conexion.getInputStream()));
        String linea;
        while ((linea = rd.readLine()) != null) {
            resultado.append(linea);
        }
        rd.close();
        return resultado.toString();
    }
}
