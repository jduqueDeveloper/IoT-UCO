#include "rest.h"

//String jsonQuery = "";

String HTTPQuery(String url){

  String query = "";

    if (http.begin(clientHttp, url))
     {
      int httpCode = http.GET();
 
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            query = http.getString();
            publishInTopic(StatusRequestTopic, "Ok");
         }
         else{
            publishInTopic(StatusRequestTopic, "The timezone probably doesn't exist, please verify the sended message");
            return "ERROR WITH TIMEZONE";
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
         publishInTopic(StatusRequestTopic, "Unable to connect with API service");
         return "ERROR WITH API";
      }
 
      http.end();
    }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
      publishInTopic(StatusRequestTopic,"Unable to initialize HTTP server");
      return "ERROR WITH HTTP SERVER";
    }
  return JsonConvert(query);
}

String JsonConvert(String JsonDoc){
       // Convert String to Json object
    char json[1024];
    JsonDoc.toCharArray(json, 1024);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);
    const char *date = doc["datetime"];

    // Get values of year / month / day / hour
    char day_of_week = doc["day_of_week"];
    char day_of_month[2] = {date[8], date[9]};
    const uint8 month = (10 * (date[5] - 48) + (date[6] - 48)) - 1; //Convert ascii to integer
    char year[4] = {date[0], date[1], date[2], date[3]};
    char hour[5] = {date[11], date[12], date[13], date[14], date[15]};

    String date_formated = "";
    date_formated += dayName(day_of_week);
    date_formated += " ";
    date_formated += day_of_month[0];
    date_formated += day_of_month[1];
    date_formated += " de ";
    date_formated += monthName(month);
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

    publishInTopic(JsonStatusTopic, "JSON Processed");
    return date_formated;
}

String dayName(char day_num)
{
       switch (day_num)
    {
    case 1:
        return "Lunes";
        break;
    case 2:
        return "Martes";
        break;
    case 3:
        return "Miercoles";
        break;
    case 4:
        return "Jueves";
        break;
    case 5:
        return "Viernes";
        break;
    case 6:
        return "Sabado";
        break;
    case 7:
        return "Domingo";
        break;
    }
    return "";
}

String monthName(uint8 month_num)
{
    switch (month_num)
    {
    case 1:
        return "Enero";
        break;
    case 2:
        return "Febrero";
        break;
    case 3:
        return "Marzo";
        break;
    case 4:
        return "Abril";
        break;
    case 5:
        return "Mayo";
        break;
    case 6:
        return "Junio";
        break;
    case 7:
        return "Julio";
        break;
    case 8:
        return "Agosto";
        break;
    case 9:
        return "Septiembre";
        break;
    case 10:
        return "Octubre";
        break;
    case 11:
        return "Noviembre";
        break;
    case 12:
        return "Diciembre";
        break;
    }
    return "";

}