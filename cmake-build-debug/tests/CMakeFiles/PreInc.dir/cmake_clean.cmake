file(REMOVE_RECURSE
  "PreInc"
  "PreInc.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/PreInc.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
