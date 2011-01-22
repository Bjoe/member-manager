# Siehe http://developer.qt.nokia.com/wiki/UnitTesting
MACRO(qt4_add_test testname testsrc)
     SET(test_${testname}_SRCS ${testsrc})

     SET(special_additional)
     FOREACH(_additional ${ARGN})
	  LIST(APPEND special_additional ${_additional})
     ENDFOREACH(_additional)
  
     qt4_automoc(${test_${testname}_SRCS} ${special_additional})
     add_executable(test_${testname} ${test_${testname}_SRCS} ${special_additional} ${test_additional})
     target_link_libraries(test_${testname} ${test_additional_lib} ${QT_LIBRARIES})

# ${QT_QTCORE_LIBRARY}
#              ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY} 
#              ${GSOAP_LIBRARIES} ${QT_QTLOCATION_LIBRARY})
  
     ADD_TEST(test_${testname} test_${testname})
ENDMACRO(qt4_add_test)

