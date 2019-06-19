g++ BattleTest.cpp Spell.cpp SpellList.cpp Bear.cpp Body.cpp BearList.cpp^
 Modifier.cpp BearBattle.cpp Player.cpp Feats.cpp RollDice.cpp^
 Display/HUD.cpp Display/BearStats.cpp Display/PlayerStats.cpp Display/Messages.cpp^
 Display/Options.cpp Display/Button.cpp Display/Highlight.cpp Display/AddSpace.cpp^
 -lsfml-graphics -lsfml-window -lsfml-system -iquote %cd% -Wall -fmax-errors=2^
 -o BattleTest.exe

@IF %errorlevel% NEQ 0 (
  GOTO END
)

g++ BearFite.cpp Spell.cpp SpellList.cpp Bear.cpp Body.cpp BearList.cpp^
 LevelUp.cpp Modifier.cpp BearBattle.cpp Player.cpp Feats.cpp RollDice.cpp^
 Display/HUD.cpp Display/BearStats.cpp Display/PlayerStats.cpp Display/Messages.cpp^
 Display/Options.cpp Display/Button.cpp Display/Highlight.cpp Display/AddSpace.cpp^
 -lsfml-graphics -lsfml-window -lsfml-system -iquote %cd% -Wall -fmax-errors=2^
 -o BearFite.exe

@ECHO/

:END
