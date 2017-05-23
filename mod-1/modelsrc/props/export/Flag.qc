$modelname	"props\flag.mdl"
$scale 10
$body mybody	"flag.smd"
$surfaceprop	metal
$cdmaterials	"models\props"

$sequence idle	"anims\action.smd" loop fps 30

$collisionmodel	"flag.smd" { $concave }