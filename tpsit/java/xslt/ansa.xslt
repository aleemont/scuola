<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
 <xsl:template match="/">
  <html>
  	<head>
  		<title>ANSAit RSS feed</title>
  		<link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css"/>
  		<meta charset="UTF-8"/>
  		<meta name="description" content="ANSA.it RSS Feed"/>
  		<meta name="keywords" content="HTML, CSS, RSS, News, ANSA, Italia, Italy"/>
  		<meta name="author" content="Alessandro Monticelli"/>
  		<meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <style>
        .background {
          background-image: url('tile_background.png');
          min-height: 1080px;

          background-attachment: fixed;
          background-position: center;
          background-repeat: no-repeat;
          background-size: cover;
        }
      </style>
  	</head>
    <body class="w3-light-grey background">
        <div class="w3-panel">
          <div class="w3-row">
            <div class="w3-col m3">&#8204;</div>
            <div class="w3-col m6 w3-center">
              <img class = "w3-animate-top" src="./logo.png" alt="ANSA.it"/>
            </div>
            <div class="w3-col m3">&#8204;</div>
          </div>
            <xsl:for-each select="rss/channel/item">
                <xsl:if test="position() &lt;= 10">
                  <div class="w3-row w3-animate-zoom">
                    <div class="w3-col m3">&#8204;</div>
                    <div class="w3-card-4 w3-white w3-col m6">    
                    	<div class = "w3-container">
                        <p class="w3-panel w3-xlarge w3-center w3-pale-green"><xsl:value-of select="title"/></p>
                        <center><i><xsl:value-of select="description"/></i></center>
                        <p class="w3-right"><xsl:value-of select="substring(pubDate, 5, 21)"/></p>
                          <xsl:variable name="link" select="link"/>
                        <div class="w3-panel">
                          <center style="position:relative; left:0%"><a href="{$link}" class="w3-button w3-ripple w3-pale-green w3-small">LINK ALL'ARTICOLO COMPLETO</a></center>
                        </div>
                      </div> 
                    </div>
                    <div class="w3-col m3">&#8204;</div>            
                  </div>
                  <br/>
                </xsl:if>
            </xsl:for-each>
        </div>
    </body>
  </html>
</xsl:template>
</xsl:stylesheet> 
