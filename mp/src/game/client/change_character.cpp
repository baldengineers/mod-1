/*
#include "cbase.h"
#include <convar.h>

void ChangeCharacter_f(const CCommand &args)
{
if (args.ArgC() < 1 | args.Arg(1) == "")
{
Msg("Usage: change_character <character number>\n");
return;
}

Msg("Changed character to character #%s\n", args.Arg(1));
}

ConCommand change_character("change_character", ChangeCharacter_f, "Change current character", 0);
*/