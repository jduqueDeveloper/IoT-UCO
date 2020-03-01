#include "WString.h"
#include "web_page.h"

String WebPage = "";

void generate_page(){
	WebPage += "<!DOCTYPE html>";
	WebPage += "<html>";
	WebPage += "<body>";
	WebPage += "  <link rel='stylesheet'";
	WebPage += "  href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css'";
	WebPage += "  integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh'";
	WebPage += "  crossorigin='anonymous'";
	WebPage += "  >";
	WebPage += "  <header>";
	WebPage += "    <div class='p-3 mb-2 bg-primary text-white text-center'>";
	WebPage += "      <h3>";
	WebPage += "        Iot Control System";
	WebPage += "        <h6><a href='/LogOut' class='text-light'>  LogOut  </a> </h6>";
	WebPage += "      </h3>";
	WebPage += "    </div>";
	WebPage += "  </header>";
	WebPage += "  <body class='bg-light'>";
	WebPage += "    <div class='text-center'>";
	WebPage += "      <h2 class='text-center'>Led</h2>";
	WebPage += "      <a href='/?Led=1'>";
	WebPage += "        <button type='button' class='btn btn-outline-success' style='width: 200px'>Encender</button>";
	WebPage += "      </a>";
	WebPage += "      <a href='/?Led=0'>";
	WebPage += "        <button type='button' class='btn btn-outline-danger' style='width: 200px'>Apagar</button>";
	WebPage += "      </a>";
	WebPage += "    </div>";
	WebPage += "    <hr class='m-5'>";
	WebPage += "    <div class='text-center'>";
	WebPage += "      <h2 class='text-center'>Load 1</h2>";
	WebPage += "      <a href='/?Load1=1'>";
	WebPage += "        <button type='button' class='btn btn-outline-success' style='width: 200px'>Encender</button>";
	WebPage += "      </a>";
	WebPage += "      <a href='/?Load1=0'>";
	WebPage += "        <button type='button' class='btn btn-outline-danger' style='width: 200px'>Apagar</button>";
	WebPage += "      </a>";
	WebPage += "    </div>";
	WebPage += "    <hr class='m-5'>";
	WebPage += "    <div class='text-center mx-5 px-5'>";
	WebPage += "      <h2 class='text-center'>Load 2</h2>";
	WebPage += "      <form action='/'>";
	WebPage += "        <input type='number' class='form-control text-center' name='Load2' min='0' max='100'><br>";
	WebPage += "        <input type='submit' class='btn btn-primary' value='Set PWM'>";
	WebPage += "      </form>";
	WebPage += "    </div>";
	WebPage += "  </body>";
	WebPage += "</html>";
}