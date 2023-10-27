################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
custom_drivers/adc_ISR.obj: C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers/adc_ISR.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib/inc" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/src" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/Optimized_MMC_PWM" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --advice:performance=all --define=CPU1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="custom_drivers/$(basename $(<F)).d_raw" --obj_directory="custom_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

custom_drivers/adc_driver.obj: C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers/adc_driver.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib/inc" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/src" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/Optimized_MMC_PWM" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --advice:performance=all --define=CPU1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="custom_drivers/$(basename $(<F)).d_raw" --obj_directory="custom_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

custom_drivers/adc_input.obj: C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers/adc_input.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib/inc" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/src" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/Optimized_MMC_PWM" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --advice:performance=all --define=CPU1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="custom_drivers/$(basename $(<F)).d_raw" --obj_directory="custom_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

custom_drivers/optimized_pwm_driver.obj: C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers/optimized_pwm_driver.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib/inc" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/src" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/Optimized_MMC_PWM" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --advice:performance=all --define=CPU1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="custom_drivers/$(basename $(<F)).d_raw" --obj_directory="custom_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

custom_drivers/pwm_driver.obj: C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers/pwm_driver.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --fp_mode=relaxed --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib/inc" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/src" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/custom_drivers" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/Optimized_MMC_PWM" --include_path="C:/Users/austi/OneDrive/Documents/SeniorProject/dsp-control-of-multilevel-inverter/f2837xd/driverlib" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" --advice:performance=all --define=CPU1 -g --c99 --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="custom_drivers/$(basename $(<F)).d_raw" --obj_directory="custom_drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


