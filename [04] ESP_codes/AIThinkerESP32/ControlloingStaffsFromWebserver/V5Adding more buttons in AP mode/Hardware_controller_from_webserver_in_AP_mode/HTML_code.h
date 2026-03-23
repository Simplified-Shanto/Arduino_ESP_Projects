const char webpageCode[] = 
R"=====(
<!DOCTYPE html>
<html>
  <head>
      <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
        <style>
        html 
        {
        background-color: rgb(61, 177, 255);
        font-family: Helvetica; 
        display: inline-block; 
        margin: 0px auto;
        text-align: center;
        }
        button 
        { 
        background-color: #ebbc14;
        border: none;
        color: white;
        padding: 16px 40px;
        text-decoration: none; 
        font-size: 30px;
        margin: 2px; 
        cursor: pointer;
        }
        .button2 
        {
        background-color: #77878A;
        }
     </style>
  </head>

  <body>
      <h1>ESP8266 Web Server</h1>
      <p><a href=\"forward"><button id = "forwardButton"> Forward </button></a></p>
      <p>
        <a href=\"left">  <button id = "leftButton"> Left   </button>   </a>
        <a href=\"right"> <button id = "rightButton"> Right </button>   </a>
      </p>
      <p><a href=\"backward"><button id = "backwardButton"> Backward </button></a></p>
  </body>
</html>

)====="; 
