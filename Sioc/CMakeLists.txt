# Sioc - simple inversion of control container
# /Sioc

set(Sioc_SRC
    Container.h
    Detail/ActivatorRegistry.h
    Detail/DeduceReturnType.h
    Detail/GenericActivator.h
    Detail/IActivator.h
    Detail/InstanceFactory.h
    Detail/IsCompleteType.h
    Detail/RegistrationModifier.h
    Detail/TypeInfo.h
    Injected.h
    Lazy.h
)

# header only library, the sources are listed to show them in IDEs
add_library(Sioc INTERFACE ${Sioc_SRC})
