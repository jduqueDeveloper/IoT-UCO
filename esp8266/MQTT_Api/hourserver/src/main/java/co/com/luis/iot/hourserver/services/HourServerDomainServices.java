package co.com.luis.iot.hourserver.services;

public interface HourServerDomainServices{
    String getHourByCountry(String country);

    String getHourByContinentCountryZone(String continent, String country, String zone) throws Exception;

    String getHourByContinent(String continent) throws Exception;

    String getHourByContinentCountry(String continent, String country) throws Exception;
}
