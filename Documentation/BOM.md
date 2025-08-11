Voici un tableau enrichi avec une colonne “Composants recommandés” pour chaque élément de ton BOM, incluant des références précises et populaires, basées sur les meilleures options disponibles en 2025. J’ai aussi intégré des liens vers les datasheets ou pages produit quand c’est pertinent pour faciliter ta recherche.

---

# BOM Contrôleur de vol ESP32-S3 — avec choix composants recommandés

| Fonction                  | Description                                | Interface / Notes                     | Composants recommandés / références                                                                                                                                                               |
| ------------------------- | ------------------------------------------ | ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **MCU principal**         | ESP32-S3 Module                            | Wi-Fi/BT + USB natif possible         | **Espressif ESP32-S3-WROOM-1** (240MHz, 16MB flash) <br> Datasheet : [esp32-s3-wroom datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_datasheet_en.pdf)    |
| **USB Interface**         | USB-C port + USB-UART                      | Via CP2104 ou intégré USB natif       | **USB-C Connector Amphenol / Molex** + **CP2104** UART bridge (Silicon Labs) <br> Datasheet CP2104: [silabs.com/cp2104](https://www.silabs.com/documents/public/data-sheets/cp2104-datasheet.pdf) |
| **Régulateur 5 V**        | Buck DC-DC Step-down 3A                    | Pour FC et VTx                        | **Texas Instruments TPS563210** (3A synchronous buck) <br> Datasheet : [ti.com TPS563210](https://www.ti.com/product/TPS563210)                                                                   |
| **Régulateur 3.3 V**      | LDO faible bruit ou buck                   | Alimentation MCU & capteurs           | **Microchip MCP1700** (LDO 250mA low noise) <br> Datasheet : [mcp1700.pdf](http://ww1.microchip.com/downloads/en/DeviceDoc/22097d.pdf) <br> ou buck **TI TPS62840** si besoin plus d’ampères      |
| **IMU**                   | Gyroscope + accéléromètre 6 axes           | SPI, FIFO                             | **ICM42688P** <br> Datasheet : [invensense.com](https://invensense.tdk.com/wp-content/uploads/2020/02/PS-ICM-42688-P-1.1.pdf)                                                                     |
| **Magnétomètre (option)** | Capteur magnétique 3 axes                  | I²C                                   | **IST8310** ([datasheet](https://www.ist-technology.com/pdf/IST8310_DS.pdf)) ou **AK09916** (plus récent)                                                                                         |
| **Baromètre**             | Mesure pression et altitude                | I2C ou SPI                            | **BMP388** (Bosch) <br> Datasheet: [bosch-sensortec.com](https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/bmp388/)                                                 |
| **Flash Blackbox**        | Mémoire SPI NOR 16 Mo                      | SPI                                   | **Winbond W25Q128JVSIQ** (128 Mbit / 16MB) <br> Datasheet : [winbond.com](https://www.winbond.com/resource-files/w25q128jv%20spi%20flash%20datasheet.pdf)                                         |
| **MOSFET logique**        | Pour contrôle VTx cut / switch caméra      | N-MOSFET, faible Rdson                | **Si2302** (SOT-23) <br> Datasheet : [vishay.com](https://www.vishay.com/docs/70317/si2302.pdf)                                                                                                   |
| **Mesure courant**        | Shunt + ampli courant                      | I2C (ex. INA226)                      | **Texas Instruments INA226** <br> Datasheet : [ti.com INA226](https://www.ti.com/product/INA226)                                                                                                  |
| **Connecteurs**           | JST-SH 6/8 pins, JST 2/4 pins              | Pour ESC, batterie, GPS, VTx          | **JST-SH 1.0mm pitch** (6 et 8 pins) <br> Mouser Digikey Amazon                                                                                                                                   |
| **Buzzer piezo actif**    | Signal sonore                              | Active buzzer, GPIO                   | **CUI Devices CMT-1205S-SMT** <br> Datasheet : [cuidevices.com](https://www.cuidevices.com/product/resource/cmt-1205s.pdf)                                                                        |
| **LED RGB**               | Indicateur status (WS2812 ou simple RGB)   | GPIO / bus numérique                  | **WS2812B** (adressable) <br> Datasheet : [worldsemi.com](https://world-semi.com/product/datasheet/WS2812B.pdf)                                                                                   |
| **Boutons tactiles**      | Bind, boot, user interface                 | GPIO digital input                    | **Omron B3F-4055** ou boutons capacitifs tactiles simples                                                                                                                                         |
| **Condensateurs**         | Electrolytique bulk + céramique decoupling | 220–470 µF low ESR + 0.1-1 µF ceramic | Panasonic, Nichicon, Murata standards                                                                                                                                                             |
| **Filtrage EMI**          | Ferrite beads, common mode choke           | Sur lignes VTx et alimentation        | **TDK MMZ1608 series ferrite beads**                                                                                                                                                              |
| **GPS Module**            | Réception GPS                              | UART (ex. NEO-M8N)                    | **u-blox NEO-M8N** <br> Datasheet : [u-blox.com](https://www.u-blox.com/sites/default/files/NEO-M8_DataSheet_%28GPS.G6-HW-09005%29.pdf)                                                           |

---

# Notes / liens utiles

* **ESP32-S3-WROOM-1** : ultra populaire, intégration Bluetooth LE 5.0 et Wi-Fi 6.
* **ICM42688P** : très utilisé pour contrôleurs de vol haut de gamme.
* **INA226** : utilisé dans les FC Betaflight pour télémétrie voltage/courant.
* **Winbond W25Q128JVSIQ** : flash SPI NOR standard dans drones FPV.
* **Si2302** : petit MOSFET logique parfait pour couper le VTx.
* **NEO-M8N** : GPS leader, bonne sensibilité, prix accessible.

---
