#include "ESC_logic.h"
#include "filter.h"
#include "debugging_buf.h"

motor_state_t MotorState;  

int16_t OpenLoopCommutationTable[512] = 
{
24824,
23220,
21810,
20562,
19449,
18450,
17549,
16732,
15988,
15306,
14681,
14105,
13572,
13078,
12619,
12190,
11790,
11416,
11064,
10734,
10422,
10129,
9851,
9588,
9339,
9102,
8877,
8663,
8459,
8265,
8079,
7901,
7731,
7568,
7412,
7262,
7119,
6980,
6847,
6719,
6596,
6477,
6362,
6252,
6145,
6041,
5941,
5845,
5751,
5661,
5573,
5488,
5405,
5325,
5247,
5172,
5098,
5027,
4958,
4890,
4824,
4761,
4698,
4638,
4579,
4521,
4465,
4410,
4357,
4304,
4253,
4204,
4155,
4108,
4061,
4016,
3971,
3928,
3885,
3844,
3803,
3763,
3724,
3686,
3649,
3612,
3576,
3541,
3506,
3472,
3439,
3407,
3375,
3343,
3312,
3282,
3252,
3223,
3195,
3166,
3139,
3112,
3085,
3059,
3033,
3007,
2982,
2958,
2934,
2910,
2887,
2864,
2841,
2819,
2797,
2775,
2754,
2733,
2712,
2692,
2672,
2652,
2633,
2614,
2595,
2576,
2558,
2540,
2522,
2504,
2487,
2470,
2453,
2436,
2420,
2404,
2388,
2372,
2356,
2341,
2326,
2311,
2296,
2282,
2267,
2253,
2239,
2225,
2211,
2198,
2185,
2171,
2158,
2145,
2133,
2120,
2108,
2095,
2083,
2071,
2059,
2048,
2036,
2025,
2013,
2002,
1991,
1980,
1969,
1958,
1948,
1937,
1927,
1917,
1906,
1896,
1886,
1876,
1867,
1857,
1848,
1838,
1829,
1819,
1810,
1801,
1792,
1783,
1775,
1766,
1757,
1749,
1740,
1732,
1723,
1715,
1707,
1699,
1691,
1683,
1675,
1667,
1660,
1652,
1645,
1637,
1630,
1622,
1615,
1608,
1601,
1594,
1586,
1580,
1573,
1566,
1559,
1552,
1546,
1539,
1532,
1526,
1519,
1513,
1507,
1500,
1494,
1488,
1482,
1476,
1470,
1464,
1458,
1452,
1446,
1440,
1434,
1429,
1423,
1417,
1412,
1406,
1401,
1395,
1390,
1385,
1379,
1374,
1369,
1364,
1359,
1353,
1348,
1343,
1338,
1333,
1328,
1323,
1318,
1313,
1309,
1304,
1299,
1294,
1290,
1285,
1281,
1276,
1271,
1267,
1263,
1258,
1254,
1249,
1245,
1241,
1236,
1232,
1228,
1224,
1220,
1215,
1211,
1207,
1203,
1199,
1195,
1191,
1187,
1183,
1180,
1176,
1172,
1168,
1164,
1160,
1157,
1153,
1149,
1146,
1142,
1138,
1135,
1131,
1128,
1124,
1121,
1117,
1114,
1110,
1107,
1103,
1100,
1097,
1093,
1090,
1087,
1083,
1080,
1077,
1074,
1070,
1067,
1064,
1061,
1058,
1055,
1052,
1049,
1046,
1043,
1039,
1036,
1034,
1031,
1028,
1025,
1022,
1019,
1016,
1013,
1010,
1007,
1005,
1002,
999,
996,
993,
991,
988,
985,
983,
980,
977,
975,
972,
969,
967,
964,
962,
959,
956,
954,
951,
949,
946,
944,
941,
939,
936,
934,
932,
929,
927,
924,
922,
920,
917,
915,
913,
910,
908,
906,
903,
901,
899,
897,
894,
892,
890,
888,
886,
883,
881,
879,
877,
875,
873,
871,
868,
866,
864,
862,
860,
858,
856,
854,
852,
850,
848,
846,
844,
842,
840,
838,
836,
834,
832,
830,
828,
826,
825,
823,
821,
819,
817,
815,
813,
812,
810,
808,
806,
804,
802,
801,
799,
797,
795,
794,
792,
790,
788,
787,
785,
783,
781,
780,
778,
776,
775,
773,
771,
770,
768,
766,
765,
763,
762,
760,
758,
757,
755,
754,
752,
750,
749,
747,
746,
744,
743,
741,
740,
738,
737,
735,
734,
732,
731,
729,
728,
726,
725,
723,
722,
720,
719,
717,
716,
715,
713,
712,
710,
709,
707,
706,
705,
703,
702,
701,
699,
698,
697,
695,
694,
692,
691,
690,
688,
687,
686,
685,
683
};

extern bool debuggingBit;
extern filter * mFilt;
extern debugging_buf * mDebugBuf;

#define LAST_COMMUTATION_TABLE_INDEX 140
void initMotorState()
{
    MotorState.phase = 0;
    MotorState.status = STANDBY;
    uint8_t i = 0;
    for (; i < COMMUTATION_FILTER_SIZE; i++)
    {
        MotorState.closedLoopCtrl.rollingCommutationFilter[i] = OpenLoopCommutationTable[LAST_COMMUTATION_TABLE_INDEX];
    }
    MotorState.closedLoopCtrl.filterSum = COMMUTATION_FILTER_SIZE * MotorState.closedLoopCtrl.rollingCommutationFilter[0];
}

void MotorStateTasks()
{
    switch(MotorState.status)
    {
        case STANDBY:
            if (MotorState.closedLoopCtrl.dutyCycle != 0)
            {
                MotorState.status = STARTUP;
                MotorState.openLoopCtrl.tableIndex = 0;
                MotorState.commutationTimerVal = OpenLoopCommutationTable[0];
                reset_commutation_timer(MotorState.commutationTimerVal);
                start_commutation_timer(true);
            }
            break;
        case STARTUP:
        {
            /* ramp up openLoopCtrl.tableIndex from 0 to 255, incrementing every 50ms*/
            if (check_event_timer_overflow())
            {
                static uint8_t accelerationCounter = 0;
                if (++accelerationCounter == 5)
                {
                    accelerationCounter = 0;
                    MotorState.commutationTimerVal = OpenLoopCommutationTable[++MotorState.openLoopCtrl.tableIndex];
                    if (MotorState.openLoopCtrl.tableIndex == LAST_COMMUTATION_TABLE_INDEX)
                    {
                      MotorState.openLoopCtrl.tableIndex--;
                        //MotorState.status = CLOSED_LOOP_CTRL;
                        //enable_cmp_interrupt(true);
                    }
                }
            }
        }
            break;
        case STALL:
            break;
        case OPEN_LOOP_CTRL:
            break;
        case CLOSED_LOOP_CTRL:
        {
            if (MotorState.closedLoopCtrl.newComparatorCaptureDataFlag)
            {
                MotorState.closedLoopCtrl.newComparatorCaptureDataFlag = 0;
                recalculate_commutation_time();
            }
        }
            break;
    }
}

void recalculate_commutation_time()
{
    /*uint8_t i = MotorState.closedLoopCtrl.filterIndex;
    int16_t x = MotorState.closedLoopCtrl.newComparatorCaptureData * 2;
    MotorState.closedLoopCtrl.filterSum += x - MotorState.closedLoopCtrl.rollingCommutationFilter[i];
    MotorState.closedLoopCtrl.rollingCommutationFilter[i] = x;*/

    static int x_prev = MotorState.closedLoopCtrl.newComparatorCaptureData;
    int x = MotorState.closedLoopCtrl.newComparatorCaptureData;
    mFilt->push(x - x_prev);
    x_prev = x;
    
    /* if midpoint crossing time is > half the commutation time, increment timer */
    if (x > (MotorState.commutationTimerVal / 2))
      MotorState.commutationTimerVal++;
    /* if midpoint crossing time is < 1/4 the commutation time, decrement timer */
    else if (x < (MotorState.commutationTimerVal / 8) || x < 64)
      MotorState.commutationTimerVal--;
    /* if the midpoint crossing time is increasing rapidly, increment timer */
    else if (mFilt->getAvg() > 20)
      MotorState.commutationTimerVal++;
    /* if the midpoint crossing time is decreasing rapidly, decrement timer */
    //else if (mFilt->getAvg() < -20)
    //  MotorState.commutationTimerVal++;
    
//    /*debugging only */
//    MotorState.commutationTimerVal = -1333;
//    if (MotorState.commutationTimerVal < -1350)
//    {
//        MotorState.commutationTimerVal = -1350;
//    }
//    if (MotorState.commutationTimerVal > -1310)
//    {
//        MotorState.commutationTimerVal = -1310;
//    }
    /*MotorState.closedLoopCtrl.filterIndex++;
    MotorState.closedLoopCtrl.filterIndex %= COMMUTATION_FILTER_SIZE;
*/
    mDebugBuf->push(x, MotorState.commutationTimerVal);
    if (debuggingBit)
    {
      /* int count = 0;
      if (count < 150)
        count++;
      else
      {
        Serial.println("debugging bit off");
        debuggingBit = false;
        count = 0;
      }
        
      Serial.print(MotorState.commutationTimerVal);Serial.print('\t');Serial.println(x);*/
      mDebugBuf->printAll();
      Serial.println("----");
      debuggingBit = false;
    }
}

#ifndef CCW_OPERATION

void commutate()
{
    switch (MotorState.phase)
    {
        /* Phase 0: Power phases A/C, B floats */
        case 0:
        {
            enable_cmp_interrupt(false);
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            MotorState.phase = 1;
        }
        break;
        /* Phase 1: Power phases B/C, A floats; comparator on */
        case 1:
        {
            PHASE_B_HIGH();
            PHASE_C_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_A();
			if (MotorState.status == CLOSED_LOOP_CTRL)
			{
				delayMicroseconds(10);
				enable_cmp_interrupt(true);
			}
            MotorState.phase = 2;
        }
        break;
        /* Phase 2: Power phases B/A, C floats */
        case 2:
        {
            enable_cmp_interrupt(false);
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            MotorState.phase = 3;
        }
        break;
        /* Phase 3: Power phases C/A, B floats; comparator on */
        case 3:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_B();
			if (MotorState.status == CLOSED_LOOP_CTRL)
			{
				delayMicroseconds(10);
				enable_cmp_interrupt(true);
			}
            MotorState.phase = 4;
        }
        break;
        /* Phase 4: Power phases C/B, A floats */
        case 4:
        {
            enable_cmp_interrupt(false);
            PHASE_C_HIGH();
            PHASE_B_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_C();
            MotorState.phase = 5;
        }
        break;
        /* Phase 5: Power phases A/B, C floats; comparator on */
        case 5:
        {
            PHASE_A_HIGH();
            PHASE_B_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_C();
			if (MotorState.status == CLOSED_LOOP_CTRL)
			{
				delayMicroseconds(10);
				enable_cmp_interrupt(true);
			}
            MotorState.phase = 0;
        }
        break;
        default:
        break;
    }
}

#else

void commutate()
{
    switch (MotorState.phase)
    {
        /* Phase 0: Power phases A/C, B floats; comparator on */
        case 0:
        {
            enable_cmp_interrupt(false);
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            MotorState.phase = 5;
        }
        break;
        /* Phase 1: Power phases B/C, A floats */
        case 1:
        {
            
            PHASE_B_HIGH();
            PHASE_C_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_A();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                delayMicroseconds(10);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 0;
        }
        break;
        /* Phase 2: Power phases B/A, C floats; comparator on */
        case 2:
        {
            enable_cmp_interrupt(false);
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            MotorState.phase = 1;
        }
        break;
        /* Phase 3: Power phases C/A, B floats */
        case 3:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_B();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                delayMicroseconds(10);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 2;
        }
        break;
        /* Phase 4: Power phases C/B, A floats; comparator on */
        case 4:
        {
            enable_cmp_interrupt(false);
            PHASE_C_HIGH();
            PHASE_B_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_C();
            MotorState.phase = 3;
        }
        break;
        /* Phase 5: Power phases A/B, C floats */
        case 5:
        {
            PHASE_A_HIGH();
            PHASE_B_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_C();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                delayMicroseconds(10);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 4;
        }
        break;
        default:
        break;
    }
}

#endif //#ifndef CCW_OPERATION
