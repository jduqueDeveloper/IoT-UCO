#include "rest_service.h"

enum week
{
    Domingo,
    Lunes,
    Martes,
    Miercoles,
    Jueves,
    Viernes,
    Sabado
};

enum month
{
    Enero,
    Febrero,
    Marzo,
    Abril,
    Mayo,
    Junio,
    Julio,
    Agosto,
    Septiembre,
    Octubre,
    Noviembre,
    Diciembre
};

String get_date(String timezone)
{

    String url = TIME_SERVER + timezone;
    String date = "";

    if (http.begin(client, url)) //Iniciar conexión
    {
        int httpCode = http.GET(); // Realizar petición

        if (httpCode > 0)
        {
            if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
            {
                date = http.getString(); // Obtener respuesta
            }
            else
            {
                publish(STATUS_REQ_TOPIC, "Fail, date not found for specified timezone");
                return "Fail";
            }
        }
        else
        {
            publish(STATUS_REQ_TOPIC, "Fail, couldn't connect with server");
            return "Fail";
        }
        http.end();
    }
    else
    {
        publish(STATUS_REQ_TOPIC, "Fail, coultn't begin http client");
        return "Fail";
    }
    publish(STATUS_REQ_TOPIC, "OK");
    return json_process_response(date);
}

String json_process_response(String json_response)
{

    // Convert String to Json object
    char json[1024];
    json_response.toCharArray(json, 1024);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);
    const char *date = doc["datetime"];

    // Get values of year / month / day / hour
    char year[4] = {date[0], date[1], date[2], date[3]};
    char day_of_month[2] = {date[8], date[9]};
    char hour[5] = {date[11], date[12], date[13], date[14], date[15]};
    char day_of_week = doc["day_of_week"];
    const uint8 month = (10 * (date[5] - 48) + (date[6] - 48)) - 1; //Convert ascii to integer

    // Generate date in right format;
    String date_formated = compose_date(year, month, day_of_month, day_of_week, hour);

    publish(JSON_STATUS, "JSON Processed");
    return date_formated;
}

String compose_date(char year[4], uint8 month, char day_of_month[2], char day_of_week, char hour[5])
{
    String date_formated = "";
    date_formated += get_day_name(day_of_week);
    date_formated += " ";
    date_formated += day_of_month[0];
    date_formated += day_of_month[1];
    date_formated += " de ";
    date_formated += get_month_name(month);
    date_formated += " de ";
    date_formated += year[0];
    date_formated += year[1];
    date_formated += year[2];
    date_formated += year[3];
    date_formated += " -- ";
    date_formated += hour[0];
    date_formated += hour[1];
    date_formated += hour[2];
    date_formated += hour[3];
    date_formated += hour[4];
    return date_formated;
}

String get_day_name(char day_num)
{

    switch (day_num)
    {
    case Lunes:
        return "Lunes";
        break;
    case Martes:
        return "Martes";
        break;
    case Miercoles:
        return "Miercoles";
        break;
    case Jueves:
        return "Jueves";
        break;
    case Viernes:
        return "Viernes";
        break;
    case Sabado:
        return "Sábado";
        break;
    case Domingo:
        return "Domingo";
        break;
    }
    return "";
}

String get_month_name(uint8 month)
{
    switch (month)
    {
    case Enero:
        return "Enero";
        break;
    case Febrero:
        return "Febrero";
        break;
    case Marzo:
        return "Marzo";
        break;
    case Abril:
        return "Abril";
        break;
    case Mayo:
        return "Mayo";
        break;
    case Junio:
        return "Junio";
        break;
    case Julio:
        return "Julio";
        break;
    case Agosto:
        return "Agosto";
        break;
    case Septiembre:
        return "Septiembre";
        break;
    case Octubre:
        return "Octubre";
        break;
    case Noviembre:
        return "Noviembre";
        break;
    case Diciembre:
        return "Diciembre";
        break;
    }
    return "";
}
