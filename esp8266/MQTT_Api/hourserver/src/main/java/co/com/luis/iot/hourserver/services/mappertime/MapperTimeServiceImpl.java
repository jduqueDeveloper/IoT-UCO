package co.com.luis.iot.hourserver.services.mappertime;

import co.com.luis.iot.hourserver.enums.DayOfTheWeeks;
import co.com.luis.iot.hourserver.enums.MonthOfTheYear;
import co.com.luis.iot.hourserver.services.mqttservice.MqttService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.stereotype.Service;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.TimeZone;
import java.util.concurrent.TimeUnit;

@Service
public class MapperTimeServiceImpl implements MapperTimeServices {

    @Autowired
    MqttService mqttService;

    @Override
    public String mapperTime(String timeResponse) {
        String time = "";
        try {
            JSONObject jsonObject= new JSONObject(timeResponse);
            String dayOfTheWeek = DayOfTheWeeks.values()[Integer.parseInt(jsonObject.getString("day_of_week"))].toString();
            String day = jsonObject.getString("datetime").substring(8,10);
            String month = MonthOfTheYear.values()[Integer.parseInt(jsonObject.getString("datetime").substring(5,7))].toString();
            String year = jsonObject.getString("datetime").substring(0,4);
            String hour = jsonObject.getString("datetime").substring(11,13);
            String minute = jsonObject.getString("datetime").substring(14,16);
            mqttService.publish();
            time = dayOfTheWeek + ", " + day + " de " + month + " de " + year + " -- " + hour + ":" + minute;

        } catch (Exception e) {
            e.printStackTrace();
        }
        return time;
    }
}
