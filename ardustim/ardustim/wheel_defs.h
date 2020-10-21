/* vim: set syntax=c expandtab sw=2 softtabstop=2 autoindent smartindent smarttab : */
/*
 * Arbritrary wheel pattern generator wheel definitions
 *
 * copyright 2014 David J. Andruczyk
 * 
 * Ardu-Stim software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArduStim software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any ArduStim software.  If not, see http://www.gnu.org/licenses/
 *
 */
 #ifndef __WHEEL_DEFS_H__
 #define __WHEEL_DEFS_H__
 
 #include <avr/pgmspace.h>
 
 /* Wheel patterns! 
  *
  * Wheel patterns define the pin states and specific times. The ISR runs 
  * at a constant speed related to the requested RPM. The request RPM is 
  * scaled based on the LENGTH of each wheel's array.  The reference is 
  * the 60-2 which was the first decoder designed which has 120 "edges" 
  * (transitions" for each revolution of the wheel. Any other wheel that 
  * also has 120 edges has and RPM scaling factor of 1.0. IF a wheel has 
  * less edges needed to "describe" it, it's number of edges are divided by 120 to
  * get the scaling factor which is applied to the RPM calculation.
  * There is an enumeration (below) that lists the defined wheel types, 
  * as well as an array listing the rpm_scaling factors with regards to 
  * each pattern.
  * 
  * NOTE: There is MORE THAN ONE WAY to define a wheel pattern.  You can 
  * use more edges to get to 1 deg accuracy but the side effect is that 
  * your maximum RPM is capped because of that. Currently 60-2 can run 
  * up to about 60,000 RPM, 360and8 can only do about 10,000 RPM becasue 
  * it has 6x the number of edges...  The less edges, the faster it can go... :)
  * 
  * Using more edges allows you to do things like vary the dutycycle,  
  * i.e. a simple non-missing tooth 50% duty cycle wheel can be defined 
  * with only 2 entries if you really want, but I didn't do it that way 
  * for some of the simple ones as it made it seem somewhat confusing
  * to look at as it required you to keep the rpm_scaler factor in mind.  
  * Most/all patterns show the pulses you're receive for one revolution
  * of a REAL wheel on a real engine.
  */
  
  /* Wheel types we know about...
   * This enumerations is the INDEX into the Wheels[] array of structures
   * defined in main file. That struct contains pointers to the following:
   * wheel name in a user friendly string
   * pointer to the wheel edge array used by the ISR
   * RPM scaling factor (num_edges/120 for crank wheels)
   * Number of edges in the edge array above, needed by the ISR 
   */
 typedef enum { 
   DIZZY_FOUR_CYLINDER,  /* 2 evenly spaced teeth */
   DIZZY_SIX_CYLINDER,   /* 3 evenly spaced teeth */
   DIZZY_EIGHT_CYLINDER, /* 4 evenly spaced teeth */
   SIXTY_MINUS_TWO,      /* 60-2 crank only */
   SIXTY_MINUS_TWO_WITH_CAM, /* 60-2 with 2nd trigger on cam */
   THIRTY_SIX_MINUS_ONE, /* 36-1 crank only */
   TWENTY_FOUR_MINUS_ONE,
   FOUR_MINUS_ONE_WITH_CAM, /* 4-1 crank + cam */
   EIGHT_MINUS_ONE,       /* 8-1 crank only */
   SIX_MINUS_ONE_WITH_CAM,/* 6-1 crank + cam */
   TWELVE_MINUS_ONE_WITH_CAM, /* 12-1 crank + cam */
   HYUNDAI_I10,
   MAX_WHEELS,
 }WheelType;

/* Name strings for EACH wheel type, for serial UI */
 const char dizzy_four_cylinder_friendly_name[] PROGMEM = "4 cylinder dizzy";
 const char dizzy_six_cylinder_friendly_name[] PROGMEM = "6 cylinder dizzy";
 const char dizzy_eight_cylinder_friendly_name[] PROGMEM = "8 cylinder dizzy";
 const char sixty_minus_two_friendly_name[] PROGMEM = "60-2 crank only";
 const char sixty_minus_two_with_cam_friendly_name[] PROGMEM = "60-2 crank and cam";
 const char thirty_six_minus_one_friendly_name[] PROGMEM = "36-1 crank only";
 const char twenty_four_minus_one_friendly_name[] PROGMEM = "24-1 crank only";
 const char four_minus_one_with_cam_friendly_name[] PROGMEM = "4-1 crank wheel with cam";
 const char eight_minus_one_friendly_name[] PROGMEM = "8-1 crank only (R6)";
 const char six_minus_one_with_cam_friendly_name[] PROGMEM = "6-1 crank with cam";
 const char twelve_minus_one_with_cam_friendly_name[] PROGMEM = "12-1 crank with cam";
 const char hyundai_i10_friendly_name[] PROGMEM = "Hyundai i10";
 

 /* Very simple 50% duty cycle */
 const unsigned char dizzy_four_cylinder[] PROGMEM = 
   { /* dizzy 4 cylinder */
     1,0,1,0 /* two pulses per crank revolution (one per cylinder) */
   };
   
 /* Very simple 50% duty cycle */
 const unsigned char dizzy_six_cylinder[] PROGMEM = 
   { /* dizzy 6 cylinder */
     1,0,1,0,1,0 /* three pulses per crank revolution (one per cylinder) */
   };
   
 /* Very simple 50% duty cycle */
 const unsigned char dizzy_eight_cylinder[] PROGMEM = 
   { /* dizzy 8 cyl */
     1,0,1,0,1,0,1,0 /* four pulses per crank revolution (one per cylinder) */
   };
   
 /* Standard bosch 60-2 pattern, 50% duty cyctle during normal teeth */
 const unsigned char sixty_minus_two[] PROGMEM = 
   { /* 60-2 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 1-5 */ 
     1,0,1,0,1,0,1,0,1,0,  /* teeth 6-10 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 11-15 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 16-20 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 21-25 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 26-30 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 31-35 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 36-40 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 41-45 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 46-50 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 51-55 */
     1,0,1,0,1,0,0,0,0,0   /* teeth 56-58 and 59-60 MISSING */
   };
 
 /* Bosch 60-2 pattern with 2nd trigger on rotation 2, 
  * 50% duty cyctle during normal teeth */
 const unsigned char sixty_minus_two_with_cam[] PROGMEM = 
   { /* 60-2 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 1-5 */ 
     1,0,1,0,1,0,1,0,1,0,  /* teeth 6-10 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 11-15 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 16-20 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 21-25 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 26-30 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 31-35 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 36-40 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 41-45 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 46-50 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 51-55 */
     1,0,1,0,1,0,0,0,0,0,  /* teeth 56-58 and 59-60 MISSING */
     1,0,1,0,1,0,1,0,1,0,  /* Second revolution teeth 1-5 */ 
     1,0,1,0,1,0,1,0,1,0,  /* teeth 6-10 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 11-15 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 16-20 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 21-25 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 26-30 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 31-35 */
     1,2,1,0,1,0,1,0,1,0,  /* teeth 36-40, Cam trigger on latter half of 36th */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 41-45 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 46-50 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 51-55 */
     1,0,1,0,1,0,0,0,0,0   /* teeth 56-58 and 59-60 MISSING */
   };
 
 /* Standard ford/mazda and aftermarket 36-1 pattern, 50% duty cyctle during normal teeth */  
 const unsigned char thirty_six_minus_one[] PROGMEM = 
   { /* 36-1 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 1-5 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 6-10 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 11-15 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 16-20 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 21-25 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 26-30 */
     1,0,1,0,1,0,1,0,1,0,  /* teeth 31-35 */
     0,0                   /* MISSING 36th tooth  */
   }; 
   
  /* Standard ford/mazda and aftermarket 36-1 pattern, 50% duty cyctle during normal teeth */  
 const unsigned char twenty_four_minus_one[] PROGMEM = 
   { /* 36-1 */
     1,0,1,0,1,0,  /* teeth 1-3 */
     1,0,1,0,1,0,  /* teeth 4-6 */
     1,0,1,0,1,0,  /* teeth 7-9 */
     1,0,1,0,1,0,  /* teeth 10-12 */
     1,0,1,0,1,0,  /* teeth 13-15 */
     1,0,1,0,1,0,  /* teeth 16-18 */
     1,0,1,0,1,0,  /* teeth 19-21 */
     1,0,1,0,0,0,  /* teeth 22-21 */
   }; 
   
 /* 4-1 crank signal 50% duty cycle with Cam tooth enabled during the second rotation prior to tooth 2 */
 const unsigned char four_minus_one_with_cam[] PROGMEM = 
   { /* 4-1 with cam */
     0,1,0,1,0,1,0,0,  /* Teeth 1-3, then MISSING */
     0,1,2,1,0,1,0,0   /* Tooth 5, 2nd trigger on cam between 5 and 6 
						  then 6 and 7 and MISSING 8th */
   };
   
 /* Yamaha R6 crank trigger 8 teeth missing one, (22.5deg low, 22.5deg high) 50% duty cycle during normal teeth */
 const unsigned char eight_minus_one[] PROGMEM = 
   { /* 8-1 */
     0,1,0,1,0,1,0,1,  /* Teeth 1-4 */
     0,1,0,1,0,1,0,0   /* Teeth 5-7, then MISSING */
   };
  
  /* 40deg low, 20 deg high per tooth, cam signal on second rotation during 40deg low portion of 3rd tooth */
 const unsigned char six_minus_one_with_cam[] PROGMEM = 
   { /* 6-1 with cam */
     0,0,1,0,0,1,0,0,1,  /* Teeth 1-3 */
     0,0,1,0,0,1,0,0,0,  /* Teeth 4 and 5 and MISSING 6th */
     0,0,1,0,0,1,2,2,1,  /* 2nd rev teeth 7 and 8, then 2nd trigger on cam between 8 and 9 */
     0,0,1,0,0,1,0,0,0   /* teeth 10 and 11 then missing 12th */
   };
  
  /* 25 deg low, 5 deg high, #12 is missing,  cam is high for 25 deg on second crank rotation just after tooth 21 (9) */
 const unsigned char twelve_minus_one_with_cam[] PROGMEM = 
   { /* 12-1 with cam */
     0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 1 and 2 */
     0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 3 and 4 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 5 and 6 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 7 and 8 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 9 and 10 */
	   0,0,0,0,0,1,0,0,0,0,0,0, /* Tooth 11 and MISSING twelth */
     //0,0,0,0,0,1,0,0,0,0,0,1, /* Tooth 11 and WITHOUT MISSING twelth */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* 2nd rotation: Teeth 13 and 14 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 15 and 16 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 17 and 18 */
	   0,0,0,0,0,1,0,0,0,0,0,1, /* Teeth 19 and 20 */
	   0,0,0,0,0,1,2,2,2,2,2,1, /* Tooth 21 and 22,  2nd trigger on cam between teeth 21 and 22 for 25 deg */
	   0,0,0,0,0,1,0,0,0,0,0,0  /* Totth 23 and MISSING 24th */
     //0,0,0,0,0,1,0,0,0,0,0,1  /* Totth 23 and WITHOUT MISSING 24th */
   };
   
   const unsigned char hyundai_i10[] PROGMEM =
   {
      0,0,1,1,1,1,0,1,0,1,
      0,1,0,1,0,1,0,1,0,1,
      0,1,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,

      2,2,3,3,3,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
      2,3,2,3,2,3,2,3,2,3,
   };

  #endif
