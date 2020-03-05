package co.com.luis.iot.hourserver.services.mappertime;

import co.com.luis.iot.hourserver.enums.DayOfTheWeeks;
import co.com.luis.iot.hourserver.enums.MonthOfTheYear;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.stereotype.Service;

import java.util.Calendar;

@Service
public class MapperTimeServiceImpl implements MapperTimeServices {
    @Override
    public String mapperTime(String timeResponse) {
        String time = "";
        try {
            JSONObject jsonObject= new JSONObject(timeResponse);
            Long unixtime = jsonObject.getLong("unixtime")*1000;
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(unixtime);
            String dayOfTheWeek = DayOfTheWeeks.values()[calendar.get(Calendar.DAY_OF_WEEK)].toString();
            String day = String.valueOf(calendar.get(Calendar.DAY_OF_MONTH));
            String month = MonthOfTheYear.values()[calendar.get(Calendar.MONTH)].toString();
            String year = String.valueOf(calendar.get(Calendar.YEAR));
            String hour = String.valueOf(calendar.get(Calendar.HOUR_OF_DAY));
            String minute = String.valueOf(calendar.get(Calendar.MINUTE));
            time = dayOfTheWeek + ", " + day + " de " + month + " de " + year + " -- " + hour + ":" + minute;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return time;
    }
}
