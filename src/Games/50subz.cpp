#include <Kernel/Font.h>
#include <Kernel/Sound.h>
#include <Kernel/Screen.h>
#include <Kernel/Keyboard.h>

uint step = 0;

using Time::Tps;

constexpr word notes[] = {
	440, 494, 588, 494, // Never gonna
	739, 739, 659, // Give you up

	440, 494, 588, 494, // Never gonna
	659, 659, 588, 554, 494, // Let you down

	440, 494, 588, 494, // Never gonna
	588, 659, 554, 440, // Run around
	440, 659, 588, // And desert you
	

	440, 494, 588, 494, // Never gonna
	739, 739, 659, // Make you cry

	440, 494, 588, 494, // Never gonna
	659, 659, 588, 554, 494, // Say goodbye

	440, 494, 588, 494, // Never gonna
	588, 659, 554, 440, // Tell a lie
	440, 659, 588, // And hurt you
};

constexpr uint noteCount = sizeof(notes) / sizeof(*notes);

constexpr double durations[noteCount] = {
	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .3, Tps * .3, Tps * .5, // Give you up

	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .3, Tps * .3, Tps * .4, Tps * .2, Tps * .5, // Let you down
	
	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .5, Tps * .22, Tps * .5, // Run around
	Tps * .22, Tps * .25, Tps * .5, Tps * .88, // And desert you

	
	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .3, Tps * .3, Tps * .5, // Make you cry

	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .5, Tps * .25, Tps * .22, Tps * .22, Tps * .5, // Say goodbye
	
	Tps * .22, Tps * .22, Tps * .25, Tps * .25, // Never gonna
	Tps * .5, Tps * .22, Tps * .5, // Tell a lie
	Tps * .22, Tps * .25, Tps * .5, Tps * .88, // And hurt you
};

constexpr const char* words[noteCount] = {
	"Never", "Never", "Gonna", "Gonna",
	"Give", "You", "Up",

	"Never", "Never", "Gonna", "Gonna",
	"Let", "You", "Down", "Down", "Down",
	
	"Never", "Never", "Gonna", "Gonna",
	"Run", "Around", "Around",
	"And", "Desert", "Desert", "You",


	"Never", "Never", "Gonna", "Gonna",
	"Make", "You", "Cry",

	"Never", "Never", "Gonna", "Gonna",
	"Say", "Goodbye", "Goodbye", "Goodbye", "Goodbye",

	"Never", "Never", "Gonna", "Gonna",
	"Tell", "A", "Lie",
	"And", "And", "Hurt", "You",
};


void Play()
{
	if (step >= noteCount)
	{
		Screen::Clear();
		constexpr const char msg[] = "Thanks for 50 subs <3";
		Font::DrawStr(msg, Screen::Width / 2 - (sizeof(msg) - 1) * 4, Screen::Height / 2 - 6, 0x28);
		Screen::SwapBuffers();
		return;
	}

	Sound::Beep(notes[step], durations[step]);
	
	Screen::Clear();
	Font::DrawStr(words[step], Screen::Width / 2 - (StrLen(words[step])) * 4, Screen::Height / 2 - 6);
	Screen::SwapBuffers();

	float delay = 0;
	if (step + 1 < noteCount && notes[step] == notes[step + 1])
		delay = Tps * .15;

	Time::Schedule(Play, durations[step] + delay);
	step++;
}

void Main()
{
	Time::Schedule(Play, Time::Tps);
	while (true);
}

void KeyPress(KeyCode key, word mods) {}
void KeyRelease(KeyCode key, word mods) {}