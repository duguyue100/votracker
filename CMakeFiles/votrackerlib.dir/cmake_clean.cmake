FILE(REMOVE_RECURSE
  "lib/libvotrackerlib.pdb"
  "lib/libvotrackerlib.dylib"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/votrackerlib.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
