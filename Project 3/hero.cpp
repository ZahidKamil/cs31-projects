#include <cctype>
#include <cassert>
#include <iostream>
#include <cctype>
#include <string>
using namespace std;
bool hasCorrectSyntax(string song); // 
bool isTranslatable(string song); // Helper function
string translate(string song); // Helper function
bool isColor(char c); // Helper function
bool isSlash(char c); // Helper function
int translateSong(string song, string& instructions, int& badBeat);
int main()
{
	string instruction = "Guitar Hero";
	int badbeat = -999;
	cout << translateSong("o/r5////b/", instruction, badbeat) << endl;
	cout << "badBeat is " << badbeat << endl << "Instruction is " << instruction << endl;
}
bool isSlash(char c)
{
	// c is a slash if it equals the front slash
	if (c == '/')
		return true;
	return false;
}
bool isColor(char c)
{
	// A color is any of these characters
	switch (c)
	{
	case 'G': case 'R': case 'B': case 'Y': case 'O': return true;
	case 'g': case 'r': case 'b': case 'y': case 'o': return true;
	default: return false;
	}
}
bool hasCorrectSyntax(string song)
{
	if (song == "")
	{
		//Empty string is 0 beats and a syntactically correct song.
		return true;
	}
	else if (song.size() == 1)
	{
		// songs with size 1 is basically just one beat, or the '/' character.
		if (song[0] == '/')
		{
			return true;
		}
		return false;
	}
	else if (song.size() == 2)
	{
		// song of size 2 either consists of a color followed by a slash or 2 slashes.
		if (isColor(song[0]))
		{
			if (song[1] == '/')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			// checks if song is just 2 slashes ("//")
			for (int i = 0; i < static_cast<int>(song.size()); i++)
				if (!isSlash(song[i]))
					return false;
			return true;
		}
	}
	else
	{
		// For songs with a size of 3 or larger.

		int pos = 0;
		while (pos != song.size())
		{
			if (isColor(song[pos]))
			{
				// character at given position is a color, so advance position
				pos++;
				if (isalpha(song[pos]))
				{
					// color followed by an alpha character is not syntactically correct
					return false;
				}
				else if (pos == song.size())
				{
					// song cannot just end on a color that isn't followed by a digit or slash.
					return false;
				}
				else if (isSlash(song[pos]))
				{
					// color followed by a forward slash
					pos++;
					continue;
				}
				else if (isdigit(song[pos]))
				{
					// color followed by a digit
					// advance position
					pos++;
					if (isSlash(song[pos]))
					{
						// color followed by a digit, followed by a forward slash
						pos++;
						continue;
					}
					else if (isdigit(song[pos]))
					{
						// color followed by a digit, followed by another digit
						pos++;
						if (isSlash(song[pos]))
						{
							pos++;
							continue;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
			else if (isSlash(song[pos]))
			{
				pos++;
				continue;
			}
			else
			{
				for (int i = 0; i < static_cast<int>(song.size()); i++)
				{
					if (!isSlash(song[i]))
					{
						return false;
					}
				}
				return true;
			}
		}
		return true;
	}
}

// Helper function: isTranslatable
bool isTranslatable(string song)
{
	if (!hasCorrectSyntax(song))
	{
		// Syntactically incorrect song cannot be translated
		return false;
	}
	else
	{
		int pos = 0;
		while (pos != song.size())
		{
			if (isColor(song[pos]))
			{
				pos++;
				if (isSlash(song[pos]))
				{
					// color followed by a slash
					pos++;
					continue;
				}
				else if (isdigit(song[pos]))
				{
					// color followed by a digit
					if (song[pos] == '0')
					{
						// color followed by a 0
						pos++;
						if (isSlash(song[pos]) || song[pos] == '1' || song[pos] == '0')
						{
							// length of a sustained note cannot be 0 or 1
							return false;
						}
						else
						{
							// color followed by a 0, an integer > 1
							// now we check to see if it has the right number of slashes

							int x = song[pos] - '0';
							pos++;
							for (int i = 0; i < x; i++)
							{
								if (pos == song.size() || !isSlash(song[pos]))
								{
									return false;
								}
								pos++;
							}
							continue;
						}

					}
					else if (song[pos] == '1')
					{

						// color followed by a 1
						pos++;
						if (isSlash(song[pos]))
						{
							// color followed by a 1 followed by a slash is not translatable
							return false;
						}
						else
						{
							if (isdigit(song[pos]))
							{
								pos++;
								int x = 10 + (song[pos] - '0'); //ASCII encoding to convert char to int
								for (int i = 0; i < x; i++)
								{
									if (pos == song.size() || !isSlash(song[pos]))
										return false;
									pos++;
								}
								continue;
							}
						}
					}
					else
					{
						// color followed by any digit from 2-9
						pos++;
						if (isdigit(song[pos]))
						{
							// color followed by a digit from 2-9, followed by another digit
							int x = (10 * (song[pos - 1] - '0')) + (song[pos] - '0');
							pos++;
							for (int i = 0; i < x; i++)
							{
								if (pos == song.size() || !isSlash(song[pos]))
									return false;
								pos++;
							}
							continue;
						}
						if (isSlash(song[pos]))
						{
							// color followed by a digit from 2-9, followed by a slash
							int x = song[pos - 1] - '0';
							for (int i = 0; i < x; i++)
							{
								if (pos == song.size() || !isSlash(song[pos]))
									return false;
								pos++;
							}
							continue;
						}
					}
				}
			}
			else if (isSlash(song[pos]))
			{
				pos++;
			}

		}
		return true;

	}
}

// Helper function: translate a translatable song
string translate(string song)
{
	string result = "";
	if (isTranslatable(song))
	{
		for (int pos = 0; pos < static_cast<int>(song.size()); pos++)
		{
			if (isColor(song[pos]))
			{
				char c = song[pos];
				pos++;
				if (isSlash(song[pos]) && ((isColor(song[pos + 1])) || (pos + 1) <= static_cast<int>(song.size())))
				{
					// color followed by a slash and then another color
					result += tolower(c);
					continue;
				}
				else if (((pos + 1) == song.size() || isSlash(song[pos + 1])) && isSlash(song[pos]))
				{
					result += c;
					pos++;
					while (pos != song.size() && isSlash(song[pos]))
					{
						result += 'x';
						pos++;
					}
					pos--;
					continue;
				}
				else if (isdigit(song[pos]))
				{
					// color followed by a digit
					if (song[pos] == '0')
					{
						// color followed by a 0, increase position by 1
						pos++;
						// color followed by a 0, an integer > 1 and now we check to see if it has right number of slashes
						int x = song[pos] - '0';
						pos++;
						for (int i = 0; i < x; i++)
						{
							if (pos != song.size() || isSlash(song[pos]))
							{
								result += toupper(c);
							}
							pos++;
						}
						pos--;
						continue;
					}
					else
					{
						// color followed by a digit from 2-9
						int x = song[pos] - '0';
						pos++;
						if (isSlash(song[pos]))
						{
							// color followed by a digit greater than 1 and followed by a slash
							for (int i = 0; i < x; i++)
							{
								result += toupper(c);
								pos++;
							}
							pos--;
							continue;
						}
						else if (isdigit(song[pos]))
						{
							x *= 10;
							x += song[pos] - '0';
							pos++;
							for (int i = 0; i < x; i++)
							{
								if (isSlash(song[pos]))
									result += toupper(c);
								pos++;
							}
							continue;

						}
					}
				}

			}
			else if (isSlash(song[pos]))
			{
				result += 'x';
			}
		}
	}
	return result;
}

int translateSong(string song, string& instructions, int& badBeat)
{
	int beat = 0;
	if (hasCorrectSyntax(song) && isTranslatable(song))
	{
		instructions = translate(song);
		return 0;
	}
	else if (!hasCorrectSyntax(song))
		return 1;
	else
	{
		int pos = 0;
		while (pos != song.size())
		{
			if (isColor(song[pos]))
			{
				pos++;
				if (isSlash(song[pos]))
				{
					// color followed by a slash
					pos++;
					beat++;
					continue;
				}
				else if (isdigit(song[pos]))
				{
					// color followed by a digit
					if (song[pos] == '0')
					{
						// color followed by a 0
						pos++;
						if (isSlash(song[pos]) || song[pos] == '1' || song[pos] == '0')
						{
							// length of a sustained note must be at least 2.
							beat++;
							badBeat = beat;
							return 2;
						}
						else
						{
							// color followed by a 0, an integer > 1 and now we check to see if it has right number of slashes
							int x = song[pos] - '0';
							pos++;
							for (int i = 0; i < x; i++)
							{
								beat++;
								if (pos == song.size())
								{
									badBeat = beat;
									return 4;
								}
								else if (pos != song.size() && !isSlash(song[pos]))
								{
									badBeat = beat;
									return 3;
								}
								pos++;
							}
							continue;
						}

					}
					else if (song[pos] == '1')
					{

						// color followed by a 1
						pos++;
						if (isSlash(song[pos]))
						{
							// color followed by a 1 followed by a slash is not translatable
							beat++;
							badBeat = beat;
							return 2;
						}
						else
						{
							if (isdigit(song[pos]))
							{
								// color followed by a 1 followed by another digit.
								int x = 10 + (song[pos] - '0'); //ASCII encoding to convert char to int
								pos++;
								for (int i = 0; i < x; i++)
								{
									beat++;
									if (pos == song.size())
									{
										// song ends prematurely (previously here was beat++)
										badBeat = beat;
										return 4;
									}
									else if (!isSlash(song[pos]) && pos != song.size())
									{
										badBeat = beat;
										return 3;
									}
									pos++;
								}
								continue;
							}
						}
					}
					else
					{
						// color followed by any digit from 2-9
						pos++;
						if (isdigit(song[pos]))
						{
							// collowed by a digit from 2-9, followed by another digit
							int x = (10 * (song[pos - 1] - '0')) + (song[pos] - '0');
							pos++;
							for (int i = 0; i < x; i++)
							{
								beat++;
								if (pos == song.size())
								{
									// song ends prematurely
									
									badBeat = beat;
									return 4;
								}
								else if (pos != song.size() && !isSlash(song[pos]))
								{
									badBeat = beat;
									return 3;
								}
								
								pos++;
							}
							continue;
						}
						else if (isSlash(song[pos]))
						{
							int x = song[pos - 1] - '0';
							for (int i = 0; i < x; i++)
							{
								beat++;
								if (pos == song.size())
								{
									// song ends prematurely
									badBeat = beat;
									return 4;
								}
								else if (pos != song.size() && !isSlash(song[pos]))
								{
									// A beat consisting of something other than a slash is present
									badBeat = beat;
									return 3;
								}
								pos++;
							}
							continue;
						}
					}
				}
			}
			else if (isSlash(song[pos]))
			{
				beat++;
				pos++;
			}

		}
		return 0;
	}
}


