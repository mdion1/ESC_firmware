#include "ESC_logic.h"

motor_state_t MotorState;

uint16_t OpenLoopCommutationTable[256] = 
{
    -23141	,
-20439	,
-18302	,
-16570	,
-15137	,
-13932	,
-12905	,
-12019	,
-11247	,
-10568	,
-9966	,
-9429	,
-8947	,
-8512	,
-8117	,
-7758	,
-7428	,
-7126	,
-6847	,
-6589	,
-6350	,
-6128	,
-5921	,
-5727	,
-5546	,
-5375	,
-5215	,
-5064	,
-4922	,
-4787	,
-4660	,
-4539	,
-4424	,
-4315	,
-4211	,
-4112	,
-4018	,
-3928	,
-3842	,
-3759	,
-3680	,
-3604	,
-3532	,
-3462	,
-3395	,
-3330	,
-3268	,
-3208	,
-3150	,
-3095	,
-3041	,
-2989	,
-2939	,
-2890	,
-2843	,
-2798	,
-2754	,
-2711	,
-2670	,
-2630	,
-2591	,
-2553	,
-2516	,
-2481	,
-2446	,
-2412	,
-2379	,
-2348	,
-2316	,
-2286	,
-2257	,
-2228	,
-2200	,
-2173	,
-2146	,
-2120	,
-2095	,
-2070	,
-2046	,
-2022	,
-1999	,
-1976	,
-1954	,
-1933	,
-1912	,
-1891	,
-1871	,
-1851	,
-1832	,
-1813	,
-1794	,
-1776	,
-1758	,
-1741	,
-1723	,
-1707	,
-1690	,
-1674	,
-1658	,
-1643	,
-1627	,
-1612	,
-1598	,
-1583	,
-1569	,
-1555	,
-1541	,
-1528	,
-1515	,
-1502	,
-1489	,
-1476	,
-1464	,
-1452	,
-1440	,
-1428	,
-1417	,
-1405	,
-1394	,
-1383	,
-1372	,
-1362	,
-1351	,
-1341	,
-1330	,
-1320	,
-1311	,
-1301	,
-1291	,
-1282	,
-1272	,
-1263	,
-1254	,
-1245	,
-1236	,
-1228	,
-1219	,
-1211	,
-1203	,
-1194	,
-1186	,
-1178	,
-1170	,
-1163	,
-1155	,
-1147	,
-1140	,
-1132	,
-1125	,
-1118	,
-1111	,
-1104	,
-1097	,
-1090	,
-1083	,
-1077	,
-1070	,
-1064	,
-1057	,
-1051	,
-1045	,
-1038	,
-1032	,
-1026	,
-1020	,
-1014	,
-1009	,
-1003	,
-997	,
-991	,
-986	,
-980	,
-975	,
-969	,
-964	,
-959	,
-954	,
-948	,
-943	,
-938	,
-933	,
-928	,
-923	,
-919	,
-914	,
-909	,
-904	,
-900	,
-895	,
-891	,
-886	,
-882	,
-877	,
-873	,
-868	,
-864	,
-860	,
-856	,
-852	,
-847	,
-843	,
-839	,
-835	,
-831	,
-827	,
-823	,
-820	,
-816	,
-812	,
-808	,
-805	,
-801	,
-797	,
-794	,
-790	,
-786	,
-783	,
-779	,
-776	,
-773	,
-769	,
-766	,
-763	,
-759	,
-756	,
-753	,
-749	,
-746	,
-743	,
-740	,
-737	,
-734	,
-731	,
-728	,
-725	,
-722	,
-719	,
-716	,
-713	,
-710	,
-707	,
-704	,
-701	,
-699	,
-696	,
-693	,
-690	,
-688	,
-685	,
-682	,
-680	,
-677	,
-674	,
-672	,
-669	,
-667
};

void initMotorState()
{
    MotorState.phase = 0;
    MotorState.status = STARTUP;
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
            }
            break;
        case STARTUP:
        {
            if (check_event_timer_overflow())
            {
                static uint8_t accelerationCounter = 0;
                if (++accelerationCounter > 50)
                {
                    accelerationCounter = 0;
                    MotorState.commutationTimerVal = OpenLoopCommutationTable[++MotorState.openLoopCtrl.tableIndex];
                    if (MotorState.openLoopCtrl.tableIndex == 255)
                    {
                        MotorState.status = CLOSED_LOOP_CTRL;
                        enable_cmp_interrupt(true);
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
    uint16_t a = (MotorState.commutationTimerVal - MotorState.closedLoopCtrl.newComparatorCaptureData) * 2;
    uint16_t b = MotorState.commutationTimerVal * 15 + a;
    MotorState.commutationTimerVal = b >> 4;
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
        /* Phase 0: Power phases A/C, B floats */
        case 0:
        {
            PHASE_A_HIGH();
            PHASE_C_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_A();
            ACMP_ASSIGN_PHASE_B();
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
            MotorState.phase = 0;
        }
        break;
        /* Phase 2: Power phases B/A, C floats */
        case 2:
        {
            PHASE_B_HIGH();
            PHASE_A_LOW();
            PHASE_C_TRIS();
            PWM_ASSIGN_PHASE_B();
            ACMP_ASSIGN_PHASE_C();
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
            MotorState.phase = 2;
        }
        break;
        /* Phase 4: Power phases C/B, A floats */
        case 4:
        {
            PHASE_C_HIGH();
            PHASE_A_LOW();
            PHASE_B_TRIS();
            PWM_ASSIGN_PHASE_C();
            ACMP_ASSIGN_PHASE_A();
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
            MotorState.phase = 4;
        }
        break;
        default:
        break;
    }
}

#endif //#ifndef CCW_OPERATION