


--install xmonad-contrib and dwm-tools (for dmenu)
--xmonad --recompile
import XMonad
import XMonad.Hooks.DynamicLog
import XMonad.Hooks.ManageDocks
import XMonad.Util.Run(spawnPipe)
import XMonad.Util.EZConfig(additionalKeys)
import System.IO


main = do
   xmonad $ defaultConfig
        { modMask = mod4Mask
         , borderWidth        = 2
         , normalBorderColor  = "#E80707" 
         , focusedBorderColor = "#68E807"
	 , terminal = "roxterm" }

