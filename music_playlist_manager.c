#include <libavformat/avformat.h>
#include <libavutil/dict.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

/* RUN:
	-sudo apt-get install libsdl2-dev libsdl2-mixer-dev libavformat-dev libavcodec-dev libavutil-dev -y
	-gcc music_playlist_manager.c -o music_playlist_manager -lavformat -lavcodec -lavutil -lSDL2 -lSDL2_mixer
*/

typedef struct song_s
{
	const char *name;
	int duration;
	struct song_s *next;
} song_t;

song_t *head = NULL;
song_t *add_song(song_t *head, const char *name, const int duration);
char *get_song_duration(const char *filename);
char *concat_strings(const char *str1, const char *str2);
int play_playlist(song_t *head, const char *songfolder);

int main(int argc, char *argv[])
{
	int choice;
	char name[50];
	char songfolder[12] = "resources/";
	char *songpath[100];

	while (1)
	{
		printf("Enter 1 to add a song to the playlist.\n");
		printf("Enter 2 to play the playlist.\n");
		printf("Enter 3 to exit: ");
		scanf("%d", &choice);

		if (choice == 3)
		{
			break;
		}

		if (choice != 1 && choice != 2)
		{
			printf("Invalid choice. Exiting...\n");
			break;
		}

		if (choice == 2)
		{
			printf("Playing the playlist...\n");
			play_playlist(head, songfolder);
			Mix_CloseAudio();
			SDL_Quit();
		}

		if (choice == 1)
		{
			while (1)
			{
				printf("- All songs are in the resources folder.\n");
				printf("- Input a song name that is available in the resources folder.\n");
				printf("- Enter 'done' to stop adding song(sample: short5.mp3 | done): ");
				scanf("%s", name);
				if (strcmp(name, "done") != 0)
				{
					printf("- Adding %s to the playlist...\n", name);
					*songpath = concat_strings(songfolder, name);
					printf("- Song path: %s\n", concat_strings(songfolder, name));
					printf("- Duration of the song: %s seconds\n", get_song_duration(concat_strings(songfolder, name)));
					head = add_song(head, name, atoi(get_song_duration(concat_strings(songfolder, name))));
				}
				else
				{
					break;
				}
			}
		}
	}

	return 0;
}

song_t *add_song(song_t *head, const char *name, const int duration)
{
	song_t *new_song = (song_t *)malloc(sizeof(song_t));
	new_song->name = strdup(name);
	new_song->duration = duration;
	new_song->next = NULL;

	if (head == NULL)
	{
		head = new_song;
	}
	else
	{
		song_t *current = head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_song;
	}

	return head;
}

char *get_song_duration(const char *songfolder)
{
	AVFormatContext *formatContext = NULL;

	if (avformat_open_input(&formatContext, songfolder, NULL, NULL) != 0)
	{
		printf("Could not open file: %s\n", songfolder);
		return NULL;
	}

	if (avformat_find_stream_info(formatContext, NULL) < 0)
	{
		printf("Could not find stream information\n");
		avformat_close_input(&formatContext);
		return NULL;
	}

	char *duration = (char *)malloc(10);
	sprintf(duration, "%ld", formatContext->duration / AV_TIME_BASE);

	avformat_close_input(&formatContext);
	return duration;
}

char *concat_strings(const char *str1, const char *str2)
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	char *result = (char *)malloc((len1 + len2 + 1) * sizeof(char));

	strcpy(result, str1);
	strcat(result, str2);

	return result;
}

int play_playlist(song_t *head, const char *songfolder)
{
	Mix_Music *music = NULL;
	song_t *current = head;

	/* Initialize SDL & SDL_mixer */
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error");
		return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize!");
		return -1;
	}

	if (current == NULL)
	{
		printf("No songs in the playlist yet.\n");
		return -1;
	}

	while (current != NULL)
	{
		printf("Playing %s\n", current->name);
		music = Mix_LoadMUS(concat_strings(songfolder, current->name));
		if (music == NULL)
		{
			printf("Failed to load your music!\n");
			return -1;
		}

		Mix_PlayMusic(music, 0);
		sleep(current->duration);
		current = current->next;
	}
}