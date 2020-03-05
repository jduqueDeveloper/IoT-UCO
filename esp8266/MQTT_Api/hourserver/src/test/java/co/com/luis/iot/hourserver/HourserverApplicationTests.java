package co.com.luis.iot.hourserver;

import co.com.luis.iot.hourserver.domain.HourServerDomainController;
import org.junit.Assert;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class HourserverApplicationTests {

	@Autowired
	HourServerDomainController hourServerDomainController;

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
		String continent = "America";
		String country = "Bogota";

		String time = hourServerDomainController.getHourByContinentCountry(continent, country);

		Assert.assertNotNull(time);
	}

}
