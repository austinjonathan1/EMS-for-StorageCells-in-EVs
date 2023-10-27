#define row 4 // constant # of switches
#define col 9 // used # of modules (SWs)

static void mmc_sorting_algo(optimized_mmc_module_s* mmc_obj, double voltage_level_norm)
{
    int req = 0, temp, n, i, j, k; // variable # of required modules (SWs)
    int SW_matrix[row][col];
    int SW_matrix_sorted[row][col];
    int SOC[2][col]; // pwm_channel_soc[]
    int SOC_sorted[2][col];
    int A[row][req]; // # of required columns depends on a lot of factors
    int I[req]; // indices
    int BO[req][row];
    int state_1[row] = { 1, 0, 0, 1 };
    int state_2[row] = { 0, 1, 1, 0 };
    for (i = 0; i < col; ++i) SOC[1][i] = i; // indices // tbd can be done in init

    // Fill SOC- indices matrix with SOC values
    for (i = 0; i < col; ++i) SOC[0][i] = pwm_channel_soc[i + mmc_obj->first_pwm_channel_num];

    // RESET SW_Matrix with DEFAULT VALUES
    for (i = 0; i < 2; ++i) for (j = 0; j < col; ++j) SW_matrix[i][j] = 1;
    for (i = 2; i < 4; ++i) for (j = 0; j < col; ++j) SW_matrix[i][j] = 0;

    // Sort SW_Matrix based on SOC matrix
    for (i = 0; i < row; ++i) for (j = 0; j < col; ++j) SW_matrix_sorted[i][j] = SW_matrix[i][j];
    for (i = 0; i < 2; ++i) for (j = 0; j < col; ++j) SOC_sorted[i][j] = SOC[i][j];

    for (i = 0; i < col; ++i)
    {
        for (j = i + 1; j < col; ++j)
        {
            if (SOC_sorted[0][i] < SOC_sorted[0][j])
            {
                for (k = 0; k < 2; ++k)
                {
                    temp = SOC_sorted[k][i];
                    SOC_sorted[k][i] = SOC_sorted[k][j];
                    SOC_sorted[k][j] = temp;
                }
                for (k = 0; k < row; ++k)
                {
                    temp = SW_matrix_sorted[k][i];
                    SW_matrix_sorted[k][i] = SW_matrix_sorted[k][j];
                    SW_matrix_sorted[k][j] = temp;
                }
            }
        }
    }

    //Select number of batteries greater than 50% SOC
    for (i = 0; i < col; ++i)
    {
        if (SOC_sorted[0][i] >= 50) 
        {
            req += 1;
        }
        /*If no battery is of 50% SOC, Select number of batteries greater than 20% SOC*/
        if (req == 0)
        {
            if (SOC_sorted[0][i] >= 20) 
            {
                req += 1;
            }
        }
    }

    // Extract SW_Matrix and SOC matrix based on #no of req batteries
    for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) A[i][j] = SW_matrix_sorted[i][j];
    for (i = 0; i < req; ++i) I[i] = SOC_sorted[1][i];

    //Create transpose of extracted SW_Matrix(A) and replace BO matrix with string to use required batteries.
    for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) BO[j][i] = A[i][j];
    for (n = 0; n < req; ++n)
    {
        if (0 < voltage_level_norm) for (i = 0; i < row; ++i) BO[n][i] = state_1[i];
        else for (i = 0; i < row; ++i) BO[n][i] = state_2[i];
    }

    // UN-TRANSPOSE BO matrix and update SW_Matrix for k+1th instant values
    for (i = 0; i < row; ++i) for (j = 0; j < req; ++j) A[i][j] = BO[j][i];
    for (i = 0; i < req; ++i) for (j = 0; j < row; ++j) SW_matrix[j][I[i]] = A[j][i];

    /*
    for (j = 0; j < col; ++j) 
    {
        reordered_pwm_channels[j + mmc_obj->first_pwm_channel_num] = &optimized_pwm_channel[j + mmc_obj->first_pwm_channel_num];//tbd
    }
    */
}

#define SOC_sort_algo

void optimized_mmc_module__update_levels(optimized_mmc_module_s* mmc_obj, double voltage_level_norm) {
#ifdef SOC_sort_algo
    int req;
    int req_pwm_channels[24];
#endif
    mmc_obj->interrupt_flag = false;
    // Sort the inverter levels based on battery state of charge
    if (mmc_obj->reorder_levels_flag) {
        optimized_mmc_module__get_new_soc(mmc_obj);
        //Rudimentary sort, this can be improved
        uint16_t index_1;
        uint16_t index_2;
        uint16_t temp_soc = 50;
        uint16_t temp_index = 0;
        for (index_1 = 0; index_1 < mmc_obj->num_levels; index_1++) {
            for (index_2 = 0; index_2 < mmc_obj->num_levels; index_2++) {
                if (pwm_channel_soc[index_2 + mmc_obj->first_pwm_channel_num] < temp_soc) {
                    reordered_pwm_channels[index_1 + mmc_obj->first_pwm_channel_num] = &optimized_pwm_channel[index_2 + mmc_obj->first_pwm_channel_num];
                    temp_soc = pwm_channel_soc[index_2 + mmc_obj->first_pwm_channel_num];
                    temp_index = index_2 + mmc_obj->first_pwm_channel_num;
                }
            }
            pwm_channel_soc[temp_index] = 55;
            temp_soc = 50;
        }
        mmc_obj->reorder_levels_flag = false;
    }
#ifdef SOC_sort_algo
    optimized_mmc_module__get_new_soc(mmc_obj);
    //Select number of batteries greater than 50% SOC
    for (int i = 0; i < 24; ++i) {
        if (pwm_channel_soc[i + mmc_obj->first_pwm_channel_num] >= 50) {
            req += 1;
        }
        /*If no battery is of 50% SOC, Select number of batteries greater than 20% SOC*/
        if (req == 0) {
            if (pwm_channel_soc[i + mmc_obj->first_pwm_channel_num] >= 20) {
                req += 1;
            }
        }
    }
    for (int index = 0; index < 24; index++) {
        if (pwm_channel_soc[index + mmc_obj->first_pwm_channel_num] >= 20) {
            req_pwm_channels[index + mmc_obj->first_pwm_channel_num] = 1;
        }
        else {
            req_pwm_channels[index + mmc_obj->first_pwm_channel_num] = 0;
        }
    }
#endif
    uint16_t index;
    // Separate loops for positive and negative voltages
    if (voltage_level_norm > 0) {
        double pwm_duty;
        for (index = 0; index < mmc_obj->num_levels; index++) {
            // If reference signal is below this level, keep this level off
            if (voltage_level_norm < (double)(((double)index) / (double)mmc_obj->num_levels)) {
                pwm_duty = -1;
                // If reference signal is above this level, turn it all the way on
            }
            else if (voltage_level_norm >= (double)((double)(index + 1) / (double)mmc_obj->num_levels)) {
                pwm_duty = 1;
                // If reference signal is in the middle of this level, calculate appropriate duty cycle
            }
            else {
                pwm_duty = voltage_level_norm * mmc_obj->num_levels - index;
            }
#ifdef SOC_sort_algo
            if (req_pwm_channels[index + mmc_obj->first_pwm_channel_num] == 1)
            {
                optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], pwm_duty * 50 + 50);
            }
            else
            {
                optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], 0);
            }
#else
            optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], pwm_duty * 50 + 50);
#endif
        }
    }
    else {
        // Conditions are mirror image of loop above
        double pwm_duty;
        for (index = 0; index < mmc_obj->num_levels; index++) {
            if (voltage_level_norm > -1 * (double)(((double)index) / (double)mmc_obj->num_levels)) {
                pwm_duty = 1;
            }
            else if (voltage_level_norm <= -1 * (double)((double)(index + 1) / (double)mmc_obj->num_levels)) {
                pwm_duty = -1;
            }
            else {
                pwm_duty = voltage_level_norm * mmc_obj->num_levels + index;
            }
#ifdef SOC_sort_algo
            if (req_pwm_channels[index + mmc_obj->first_pwm_channel_num] == 1)
            {
                optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], pwm_duty * 50 + 50);
            }
            else
            {
                optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], 0);
            }
#else
            optimized_pwm_driver__set_duty_cycle(reordered_pwm_channels[mmc_obj->first_pwm_channel_num + index], pwm_duty * 50 + 50);
#endif
        }
    }
}
