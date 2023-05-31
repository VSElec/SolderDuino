/*  Logo soldering station
    File: Logo.h
    Ver: 1.0
    Created on: 06/06/2020
    Author: Stefano Valfrè
*/

/*
  Site used to convert images:
  https://diyusthad.com/image2cpp
*/
#ifndef _LOGO_H
#define _LOGO_H

// 'Logo2', 128x55px
const unsigned char myLogo [] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f,
  0xff, 0xff, 0xff, 0xfc, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0xff,
  0xff, 0x81, 0xff, 0xf9, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0x87, 0x7f,
  0xff, 0x3f, 0xff, 0xf9, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x02, 0x7f, 0xff,
  0xfe, 0x7f, 0xc1, 0xf3, 0xc0, 0x7c, 0x3c, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0f, 0xff, 0xff,
  0xfe, 0x1f, 0x9c, 0xe3, 0x9c, 0xf3, 0x3c, 0x7f, 0xff, 0xff, 0xff, 0xf9, 0xe0, 0x3f, 0xff, 0xff,
  0xff, 0x87, 0x3c, 0xe7, 0x3c, 0xe7, 0x39, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xe6, 0x7c, 0xc6, 0x79, 0xc0, 0x39, 0xff, 0xff, 0xff, 0xff, 0x00, 0x07, 0xff, 0xff, 0xff,
  0xff, 0xc6, 0x79, 0xce, 0x79, 0xcf, 0xf3, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xff, 0xff,
  0xf1, 0x0e, 0x63, 0x8e, 0x03, 0xc6, 0x73, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0x7f, 0xff,
  0xfc, 0x7f, 0x9f, 0xff, 0x3f, 0xf1, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe5, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x98, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9e, 0x7c, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x39, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf7, 0xe4, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xc2, 0x0f, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x00, 0x7f, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xce, 0x00, 0x98, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x1c, 0xff, 0xe0, 0x7f, 0xe0, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xfc, 0xe7, 0xff, 0xff, 0xff, 0xc6, 0x1f, 0xff, 0xc7, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xf3, 0x7f, 0xff, 0xff, 0xff, 0xcf, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xdd, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8c, 0x73, 0x9e, 0x03, 0xc4, 0x7f,
  0xff, 0xff, 0xff, 0xfe, 0x77, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x9c, 0xf3, 0x9c, 0x73, 0x1e, 0x7f,
  0xff, 0xff, 0xff, 0xf9, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x18, 0xe7, 0x3c, 0xe7, 0x3c, 0x7f,
  0xff, 0xff, 0xff, 0x8e, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3e, 0x39, 0xe7, 0x39, 0xe6, 0x7c, 0xff,
  0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0xf1, 0x8e, 0x79, 0xce, 0x39, 0xff,
  0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x03, 0xf8, 0x4e, 0x73, 0xcf, 0x07, 0xff,
  0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#endif
