package co.com.luis.iot.hourserver.services;

import co.com.luis.iot.hourserver.services.mappertime.MapperTimeServices;
import co.com.luis.iot.hourserver.services.request_http.RequestHttpGetServices;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.configurationprocessor.json.JSONObject;
import org.springframework.stereotype.Service;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

@Service
public class HourServerDomainServicesImpl implements HourServerDomainServices {

    @Autowired
    RequestHttpGetServices requestHttpGetServices;
    @Autowired
    MapperTimeServices mapperTimeServices;

    static SimpleDateFormat FORMATTER = new SimpleDateFormat("MM/dd/yyyy 'at' hh:mma z");

    @Override
    public String getHourByCountry(String country) {
        TimeZone timeZone = TimeZone.getTimeZone(country);
        Date currentDate = new Date();
        FORMATTER.setTimeZone(timeZone);
        return FORMATTER.format(currentDate);
    }

    @Override
    public String getHourByContinent(String continent) throws Exception {
        String url = "http://worldtimeapi.org/api/timezone/"+continent;
        String timeResponse = requestHttpGetServices.requestHttpGet(url);
        return mapperTimeServices.mapperTime(timeResponse);
    }

    @Override
    public String getHourByContinentCountry(String continent, String country) throws Exception {
        String url = "http://worldtimeapi.org/api/timezone/"+continent+"/"+country;
        String timeResponse = requestHttpGetServices.requestHttpGet(url);
        return mapperTimeServices.mapperTime(timeResponse);
    }

    @Override
    public String getHourByContinentCountryZone(String continent, String country, String zone) throws Exception {
        String url = "http://worldtimeapi.org/api/timezone/"+continent+"/"+country+"/"+zone;
        String timeResponse = requestHttpGetServices.requestHttpGet(url);
        return mapperTimeServices.mapperTime(timeResponse);
    }





}
