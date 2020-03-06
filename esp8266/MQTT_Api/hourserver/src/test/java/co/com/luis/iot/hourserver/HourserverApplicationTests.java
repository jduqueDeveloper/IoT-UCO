package co.com.luis.iot.hourserver;

import co.com.luis.iot.hourserver.domain.HourServerDomainController;
import co.com.luis.iot.hourserver.services.mappertime.MapperTimeServiceImpl;
import org.junit.Assert;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class HourserverApplicationTests {

	@Autowired
	HourServerDomainController hourServerDomainController;
	@Autowired
	MapperTimeServiceImpl mapperTimeService;

	@Test
	public void getHourByCountryTest(){
		//Given
		String country = "Australia/Lindeman";
		//When
		String time = hourServerDomainController.getHourByCountry(country);
		//Then
		Assert.assertNotNull(time);
	}

	@Test
	public void getHourByCountryWithCloudServerTest() throws Exception {
		String continent = "Europe";
		String country = "Amsterdam";

		String time = hourServerDomainController.getHourByContinentCountry(continent, country);

		Assert.assertNotNull(time);
	}

	@Test
	public void mapperTest() throws Exception{
		String time = "{\"week_number\":10,\"utc_offset\":\"+01:00\",\"utc_datetime\":\"2020-03-06T17:48:07.737695+00:00\",\"unixtime\":1583516887,\"timezone\":\"Europe/Amsterdam\",\"raw_offset\":3600,\"dst_until\":null,\"dst_offset\":0,\"dst_from\":null,\"dst\":false,\"day_of_year\":66,\"day_of_week\":5,\"datetime\":\"2020-03-06T18:48:07.737695+01:00\",\"client_ip\":\"181.139.43.50\",\"abbreviation\":\"CET\"}";
		mapperTimeService.mapperTime(time);

	}

}
