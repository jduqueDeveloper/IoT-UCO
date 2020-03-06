package co.com.luis.iot.hourserver.domain;

import co.com.luis.iot.hourserver.services.HourServerDomainServices;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/getHourByCountryWithCloudServer")
public class HourServerDomainController {

    @Autowired
    HourServerDomainServices hourServerDomainServices;

    @GetMapping("/getHourByCountry/{country}")
    public String getHourByCountry(@PathVariable(value = "country") String country){
        return hourServerDomainServices.getHourByCountry(country);
    }

    @GetMapping("/{continent}")
    public String getHourByContinent(@PathVariable(value = "continent") String continent) throws Exception {
        return hourServerDomainServices.getHourByContinent(continent);
    }

    @GetMapping("/{continent}/{country}")
    public String getHourByContinentCountry(@PathVariable(value = "continent") String continent, @PathVariable(value = "country") String country) throws Exception {
        return hourServerDomainServices.getHourByContinentCountry(continent, country);
    }

    @GetMapping("/{continent}/{country}/{zone}")
    public String getHourByContinentCountryZone(@PathVariable(value = "continent") String continent, @PathVariable(value = "country") String country, @PathVariable(value = "zone") String zone) throws Exception {
        return hourServerDomainServices.getHourByContinentCountryZone(continent, country, zone);
    }
}
