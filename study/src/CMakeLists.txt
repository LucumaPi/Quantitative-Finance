#set(HEADER_LIST "${DuffyProject_SOURCE_DIR}/include/duffy/*.hh")

add_library(duffy#SHARED,STATIC,MODULE
    DatasimDate.cc
    GenericInequalities.cc
    Inequalities.cc
    Person.cc
    EuropeanOption.cc
    SimpleBondPricing.cc
    Point.cc
    Complex.cc
    ComplexArray.cc
    PayoffNamespace.cc
    DatesimDateTime.cc
    OneFactorPayoff.cc
    BullSpreadPayoff.cc
    CallPayoff.cc
    Payoff.cc
    Rectangle.cc
    #MultiAssetPayoff.cc
    Array.cc
    ArrayStructure.cc
    FullArray.cc
    Vector.cc
    DatasimException.cc
    Range.cc
    NumericMatrix.cc
    Tensor.cc
    ArrayMechanisms.cc
    PointTemplate.cc
    Set.cc
    Matrix.cc
    Property.cc
    FullMatrix.cc
    MatrixStructure.cc
    PropertyThing.cc
    SimplePropertySet.cc
    StringConversions.cc
    AssocArray.cc
    #AssocMatrix.cc
    Lattice.cc
    MatrixMechanisms.cc
    #LatticeMechanisms.cc
    # GenericComposite.cc
    BinomialMethod.cc
    BinomialLatticeStrategy.cc
    # BackupEuropeanOption2.cc
    IBVP.cc
    IBVPImp.cc
    IBVPSolver.cc
    BSIBVPImp.cc
    EEulerIBVPSolver.cc
    IEulerIBVPSolver.cc
    Mesher.cc
    LUSolver.cc
    STDImp.cc
    # ExcelDriver.cc
    # ExcelMechanisms.cc
    #${HEADER_LIST}
)

target_include_directories(duffy PUBLIC ../include)