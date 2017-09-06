CC = arm-linux-gcc
CFLAGS = -O2
OBJS = mic.c audio.c mic_audio_test.c hardware_sdk.h

mic_audio_test : $(OBJS)
	$(CC)  $(CFLAGS) $^ -o $@
mic_test : mic.c mic_test.c hardware_sdk.h
	$(CC)  $(CFLAGS) $^ -o $@
audio_test : audio.c audio_test.c hardware_sdk.h
	$(CC)  $(CFLAGS) $^ -o $@

.PHYONE : clean
clean :
	rm -f mic.o audio.o mic_audio_test.o mic_audio_test mic_test audio_test
