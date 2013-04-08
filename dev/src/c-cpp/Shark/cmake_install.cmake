# Install script for directory: /home/cg/dev/master-thesis/dev/src/c-cpp/Shark

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libshark.so.2.3.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libshark.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/libshark.so.2.3.0"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/libshark.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libshark.so.2.3.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libshark.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/SharkDefs.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Array" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/Array.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/Array2D.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/ArrayIo.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/ArrayOp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/ArraySort.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Array/ArrayTable.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Rng" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Bernoulli.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Binomial.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Cauchy.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/DiffGeometric.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Dirichlet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/DiscreteUniform.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Erlang.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Gamma.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Geometric.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/GlobalRng.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/HyperGeometric.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/LogNormal.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/NegExponential.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Normal.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Poisson.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/RNG.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/RandomVar.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Uniform.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Rng/Weibull.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/LinAlg" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/LinAlg/LinAlg.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/LinAlg/VecMat.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/LinAlg/arrayoptimize.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/LinAlg/fft.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/FileUtil" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/FileUtil/FileUtil.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/FileUtil/IOTools.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/FileUtil/Params.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/EALib" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/CMA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/CMSA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/Chromosome.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ChromosomeCMA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ChromosomeCMACholesky.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ChromosomeFactory.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ChromosomeT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ElitistCMA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/Individual.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/IndividualT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/Interval.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/MultiObjectiveFunctions.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ObjectiveFunction.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/ObjectiveFunctions.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/OnePlusOneES.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/PVMinterface.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/Population.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/PopulationT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/SearchAlgorithm.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/EALib/UncertaintyQuantification.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MOO-EALib" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/ArchiveMOO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/Hypervolume.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/IndividualMOO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/MO-CMA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/MOOMeasures.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/MOOTestFunctions.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/NSGA2.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/PopulationMOO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/README"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/RMMEDA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/SelectionMOO-Impl.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/SelectionMOO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/MOO-EALib/TestFunction.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ReClaM" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/AdpBP.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ArtificialDistributions.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/BFGS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/BinaryCriterion.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CG.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CMAOptimizer.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ClassificationError.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CMAC.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ComponentWiseModel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ConcatenatedModel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CoverTree.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CrossEntropy.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CrossEntropyIndependent.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/CrossValidation.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/DF_CrossEntropy.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/DF_CrossEntropyIndependent.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/DF_MeanSquaredError.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Dataset.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/EarlyStopping.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ErrorFunction.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ErrorPercentage.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/FFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/FFNetSource.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/GaussKernel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/GaussianProcess.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/GridSearch.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/InverseClassSeparability.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/JaakkolaHeuristic.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KTA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KalmanFilter.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelFunction.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelKMeans.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelMeanClassifier.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelNearestNeighbor.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelNearestNeighborRegression.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LDA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LMSEFFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LOO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LinOutFFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LinOutMSEBFFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LinearEquation.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LinearModel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/LinearRegression.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/MSEFFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/MSERBFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/MSERNNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/McSvmApproximation.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/MeanSquaredError.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Model.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ModelInterface.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ModelWithErrorFunction.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NegativeLogLikelihood.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NegativePolarization.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NetParams.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NoisyRprop.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NoisySvmLikelihood.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/NormedModels.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Optimizer.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/PCA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/FisherLDA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Paraboloid.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Perceptron.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ProbenBNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ProbenNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QuadraticProgram.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/KernelMatrices.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Utilities.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QpSvmDecomp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QpBoxDecomp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QpMcDecomp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QpMcStzDecomp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/QpEbCsDecomp.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Quickprop.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/RBFNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ROC.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/RadiusMargin.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Rprop.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SigmoidFit.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SigmoidModel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Softmax.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SpanBound1.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SpanBound2.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SpanBoundA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SquaredError.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SteepestDescent.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/StochasticGradientDescent.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Svm.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/SvmApproximation.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/TanhNet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/ValidationError.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/Variance.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/VarianceEstimator.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/WTA.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/ReClaM/createConnectionMatrix.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Mixture" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/CodeBook.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/KernelDensity.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/LocalLinearRegression.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/MixtureLinearRegression.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/MixtureModel.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/MixtureOfGaussians.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/RBFN-PTO.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/RBFN.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Mixture/RandomVector.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/TimeSeries" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/BimodalBrownianProcess.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/Counter.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/DiscreteMackeyGlass.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/Embedding.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/Generator.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/IOGenerator.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/IOSamples.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/Lorenz63.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/Lorenz84.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/MackeyGlass.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/NoisyIOSamples.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/NoisyMackeyGlass.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/RK4-1D.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/RK4.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/TimeSeries/SelectComponent.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Fuzzy" TYPE FILE FILES
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/BellFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/BellLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/ComposedFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/ComposedLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/ComposedNDimFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/ConstantFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/ConstantLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/CustomIM.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/CustomizedFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/CustomizedLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/FuzzyException.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/FuzzyIncludes.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/FuzzyRelation.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/FuzzySet.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/GeneralizedBellFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/GeneralizedBellLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/HomogenousNDimFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/Implication.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/InferenceMachine.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/InfinityFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/InfinityLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/LinguisticTerm.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/LinguisticVariable.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/MamdaniIM.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/NDimFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/Operators.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/RCObject.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/RCPtr.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/Rule.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/RuleBase.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/RuleBaseGenerator.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SigmoidalFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SigmoidalLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SingletonFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SingletonLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SugenoIM.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/SugenoRule.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/TrapezoidFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/TrapezoidLT.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/TriangularFS.h"
    "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/include/Fuzzy/TriangularLT.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/examples/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/cg/dev/master-thesis/dev/src/c-cpp/Shark/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
