#include "ESC_logic.h"

motor_state_t MotorState;

int16_t OpenLoopCommutationTable[256] = 
{
   -24824	,
-23220	,
-21810	,
-20562	,
-19449	,
-18450	,
-17549	,
-16732	,
-15988	,
-15306	,
-14681	,
-14105	,
-13572	,
-13078	,
-12619	,
-12190	,
-11790	,
-11416	,
-11064	,
-10734	,
-10422	,
-10129	,
-9851	,
-9588	,
-9339	,
-9102	,
-8877	,
-8663	,
-8459	,
-8265	,
-8079	,
-7901	,
-7731	,
-7568	,
-7412	,
-7262	,
-7119	,
-6980	,
-6847	,
-6719	,
-6596	,
-6477	,
-6362	,
-6252	,
-6145	,
-6041	,
-5941	,
-5845	,
-5751	,
-5661	,
-5573	,
-5488	,
-5405	,
-5325	,
-5247	,
-5172	,
-5098	,
-5027	,
-4958	,
-4890	,
-4824	,
-4761	,
-4698	,
-4638	,
-4579	,
-4521	,
-4465	,
-4410	,
-4357	,
-4304	,
-4253	,
-4204	,
-4155	,
-4108	,
-4061	,
-4016	,
-3971	,
-3928	,
-3885	,
-3844	,
-3803	,
-3763	,
-3724	,
-3686	,
-3649	,
-3612	,
-3576	,
-3541	,
-3506	,
-3472	,
-3439	,
-3407	,
-3375	,
-3343	,
-3312	,
-3282	,
-3252	,
-3223	,
-3195	,
-3166	,
-3139	,
-3112	,
-3085	,
-3059	,
-3033	,
-3007	,
-2982	,
-2958	,
-2934	,
-2910	,
-2887	,
-2864	,
-2841	,
-2819	,
-2797	,
-2775	,
-2754	,
-2733	,
-2712	,
-2692	,
-2672	,
-2652	,
-2633	,
-2614	,
-2595	,
-2576	,
-2558	,
-2540	,
-2522	,
-2504	,
-2487	,
-2470	,
-2453	,
-2436	,
-2420	,
-2404	,
-2388	,
-2372	,
-2356	,
-2341	,
-2326	,
-2311	,
-2296	,
-2282	,
-2267	,
-2253	,
-2239	,
-2225	,
-2211	,
-2198	,
-2185	,
-2171	,
-2158	,
-2145	,
-2133	,
-2120	,
-2108	,
-2095	,
-2083	,
-2071	,
-2059	,
-2048	,
-2036	,
-2025	,
-2013	,
-2002	,
-1991	,
-1980	,
-1969	,
-1958	,
-1948	,
-1937	,
-1927	,
-1917	,
-1906	,
-1896	,
-1886	,
-1876	,
-1867	,
-1857	,
-1848	,
-1838	,
-1829	,
-1819	,
-1810	,
-1801	,
-1792	,
-1783	,
-1775	,
-1766	,
-1757	,
-1749	,
-1740	,
-1732	,
-1723	,
-1715	,
-1707	,
-1699	,
-1691	,
-1683	,
-1675	,
-1667	,
-1660	,
-1652	,
-1645	,
-1637	,
-1630	,
-1622	,
-1615	,
-1608	,
-1601	,
-1594	,
-1586	,
-1580	,
-1573	,
-1566	,
-1559	,
-1552	,
-1546	,
-1539	,
-1532	,
-1526	,
-1519	,
-1513	,
-1507	,
-1500	,
-1494	,
-1488	,
-1482	,
-1476	,
-1470	,
-1464	,
-1458	,
-1452	,
-1446	,
-1440	,
-1434	,
-1429	,
-1423	,
-1417	,
-1412	,
-1406	,
-1401	,
-1395	,
-1390	,
-1385	,
-1379	,
-1374	,
-1369	,
-1364	,
-1359	,
-1353	,
-1348	,
-1343	,
-1338	,
-1333
};

void initMotorState()
{
    MotorState.phase = 0;
    MotorState.status = STANDBY;
    uint8_t i = 0;
    for (; i < 16; i++)
    {
        MotorState.closedLoopCtrl.rollingCommutationFilter[i] = OpenLoopCommutationTable[255];
    }
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
                if (++accelerationCounter == 10)
                {
                    accelerationCounter = 0;
                    MotorState.commutationTimerVal = OpenLoopCommutationTable[++MotorState.openLoopCtrl.tableIndex];
                    if (MotorState.openLoopCtrl.tableIndex == 255)
                    {
                        MotorState.status = CLOSED_LOOP_CTRL;
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
    static int16_t filterSum = 16 * (-1333);
    uint8_t i = MotorState.closedLoopCtrl.filterIndex;
    MotorState.closedLoopCtrl.filterIndex = i == 0 ? 15 : i - 1;
    
    int16_t x = (MotorState.commutationTimerVal - MotorState.closedLoopCtrl.newComparatorCaptureData) * 2;
    filterSum += x - MotorState.closedLoopCtrl.rollingCommutationFilter[i];
    MotorState.closedLoopCtrl.rollingCommutationFilter[i] = x;
    MotorState.commutationTimerVal = filterSum / 16;
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
            enable_cmp_interrupt(true);
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
            enable_cmp_interrupt(true);
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
            enable_cmp_interrupt(true);
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
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_B();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                blank(500);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 5;
        }
        break;
        /* Phase 1: Power phases B/C, A floats */
        case 1:
        {
            enable_cmp_interrupt(false);
            PHASE_B_HIGH();
            PHASE_C_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_B();
            MotorState.phase = 0;
        }
        break;
        /* Phase 2: Power phases B/A, C floats; comparator on */
        case 2:
        {
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_C();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                blank(500);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 1;
        }
        break;
        /* Phase 3: Power phases C/A, B floats */
        case 3:
        {
            enable_cmp_interrupt(false);
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            MotorState.phase = 2;
        }
        break;
        /* Phase 4: Power phases C/B, A floats; comparator on */
        case 4:
        {
            PHASE_C_HIGH();
            PHASE_B_LOW();
            PHASE_A_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_A();
            if (MotorState.status == CLOSED_LOOP_CTRL)
            {
                blank(500);
                enable_cmp_interrupt(true);
            }
            MotorState.phase = 3;
        }
        break;
        /* Phase 5: Power phases A/B, C floats */
        case 5:
        {
            enable_cmp_interrupt(false);
            PHASE_A_HIGH();
            PHASE_B_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_A();
            MotorState.phase = 4;
        }
        break;
        default:
        break;
    }
}

#endif //#ifndef CCW_OPERATION