/*
NOTE: the '\n' are very precise and have to be exactly like as in this file for the test cases to pass
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief Returns the appropriate index for the given ASCII character in the ASCII to Braille map. Indexes 0-25 for letters 'a'-'z', 0-8 for digits '1'-'9', index 9 for digit '0', 26 for ' ' (SPACE), and -1 for all other characters (that our translator does not handle).
 *
 */
int map_index(char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  if (c >= '1' && c <= '9')
    return c - '1';
  if (c == '0')
    return 9;
  if (c == ' ')
    return 26;
  return -1;
}

/**
 * @brief Reports whether the given character can be translated to a Braille symbol (for this program, alphabets, digits, and the SPACE character only).
 *
 */
int can_translate_to_braille(char ch)
{
  return (map_index(ch) != -1);
}

/**
 * @brief Return the string representing the given ASCII character in the given ASCII-to-Braille map.
 *
 * Requires: ch can be translated to Braille and map is properly populated.
 *
 */
char *ascii_to_braille(char ch, char *map[])
{
  return map[map_index(ch)];
}

/**
 * @brief Print the Braille-equivalent of the given character using the given map on the console, if the character can be translated to Braille; ignores otherwise.
 *
 * Requires: map is properly populated
 *
 */
void print_braille(char ch, char *map[])
{
  ch = tolower(ch);
  if (!can_translate_to_braille(ch))
    return;

  char *braille = ascii_to_braille(ch, map);

  printf("%c%c\n", braille[0], braille[3]);
  printf("%c%c\n", braille[1], braille[4]);
  printf("%c%c\n", braille[2], braille[5]);

  printf("\n");
}
/**
 * @brief Adds a dot in the given Braille representation at the given position (indexing for the position starts at 1 in Braille; your representation may start at 0.)
 *
 */
void add_dot_at_pos(char *b, int pos)
{
  b[pos - 1] = '.';
}

/**
 * @brief Creates and returns the ASCII-to-Braille map as described.
 *
 */
char **generate_map()
{
  const int MAP_LENGTH = 27, ENCODING_LENGTH = 7;
  char **m = calloc(MAP_LENGTH, sizeof(char *));
  for (int i = 0; i < MAP_LENGTH; ++i)
    m[i] = calloc(ENCODING_LENGTH, sizeof(char));

  /* hard-coding the first decade (and SPACE) */
  strcpy(m[map_index('a')], ".-----");
  strcpy(m[map_index('b')], "..----");
  strcpy(m[map_index('c')], ".--.--");
  strcpy(m[map_index('d')], ".--..-");
  strcpy(m[map_index('e')], ".---.-");
  strcpy(m[map_index('f')], "..-.--");
  strcpy(m[map_index('g')], "..-..-");
  strcpy(m[map_index('h')], "..--.-");
  strcpy(m[map_index('i')], "-.-.--");
  strcpy(m[map_index('j')], "-.-..-");
  strcpy(m[map_index(' ')], "------");

  /* deriving the second decade by adding a dot at position 3 */
  for (char c = 'k'; c <= 't'; ++c)
  {
    char from = c - 10;
    strcpy(m[map_index(c)], m[map_index(from)]);
    add_dot_at_pos(m[map_index(c)], 3);
  }

  /* deriving the third decade by adding a dot at position 6 and handling special cases */
  for (char c = 'u'; c <= 'z'; ++c)
  {
    char from = c - 10;
    if (c == 'w')
      from = 'j';
    else if (c == 'x' || c == 'y' || c == 'z')
      from = from - 1;
    strcpy(m[map_index(c)], m[map_index(from)]);
    add_dot_at_pos(m[map_index(c)], 6);
  }

  return m;
}

/**
 * @brief Free the heap memory held by the map.
 *
 */
void release_map(char **m)
{
  const int MAP_LENGTH = 27;
  for (int i = 0; i < MAP_LENGTH; ++i)
    free(m[i]);
  free(m);
}

/**
 * @brief Displays the given ASCII-to-Braille map on the console.
 *
 */
void display_map(char *m[])
{
  for (char c = 'a'; c <= 'z'; ++c)
  {
    printf("%c: ", c);
    printf("%s\n", ascii_to_braille(c, m));
  }
  for (char c = '0'; c <= '9'; ++c)
  {
    printf("%c: ", c);
    printf("%s\n", ascii_to_braille(c, m));
  }
  printf(" : ");
  printf("%s\n", ascii_to_braille(' ', m));
}

/**
 * @brief Returns a FILE's handle after opening it for reading. Keeps prompting the user for a valid path if it cannot open it.
 *
 */
FILE *open_file_to_read()
{
  FILE *fp = NULL;
  char path[256];
  while (fp == NULL)
  {
    printf("Enter valid file path: ");
    scanf("%s", path);
    fp = fopen(path, "r");
    if (fp == NULL)
      printf("%s: No such file.\n", path);
  }
  return fp;
}

/**
 * @brief Translates the contents of the given ASCII file to Braille using the given character map.
 *
 * Requires: fp is opened for reading map is properly populated
 *
 */
void translate_ascii_to_braille(FILE *fp, char *map[])
{
  char ch;
  while ((ch = fgetc(fp)) != EOF)
  {
    print_braille(ch, map);
  }
}

int main()
{

  printf("This program supports three operations:\n");
  printf("\t1. Display the ASCII to Braille character map\n");
  printf("\t2. Translate a single ASCII character to Braille\n");
  printf("\t3. Translate a text file to Braille\n");
  printf("Enter your option: ");
  int option = 0;
  scanf("%d", &option);

  char **map = generate_map();
  if (option == 1)
  {
    display_map(map);
  }
  else if (option == 2)
  {
    char input[2];
    printf("Enter a letter or a digit: ");
    scanf("%s", input);

    printf("\n'%s' in Braille:\n", input);
    print_braille(input[0], map);
  }
  else if (option == 3)
  {
    FILE *fp = open_file_to_read();

    printf("\nBraille version:\n");
    translate_ascii_to_braille(fp, map);

    fclose(fp);
  }
  release_map(map);

  return 0;
}