/**
 * IModule.h
 *
 * Project : 	Apirate
 * Created on:  Jan 2, 2016
 * Author: 	    Apirate Crew
 */

#pragma once

#include "eModule.h"
#include "ILogger.h"
#include "IQuery.h"
#include "IExecutionProcess.h"
#include "IConfiguration.h"

namespace Apirate {
	/**
	* @brief Basic interface for modules
	* @details This class allows the implementor to define a basic interface for
	* its modules and what minimum informations they must have.
	*/
	class IModule {
	public:
		virtual ~IModule() {};
    
    typedef ISocket*    (*socketBuilder)(int fd);

		/**
		* @brief Allows the module to init itself
		* @details This method allows the implementor to have a specific
		* location to build the module before it starts its execution.
		* @details A pointer to the configuration of the executable.
		* @return An int being the error or success code.
		*/
		virtual int init(IConfiguration* conf = nullptr) = 0;

		/**
		* @brief Getter for the module's name
		* @details This method allows the implementor to retrieve the name of
		* the module.
		* @return The name of the module.
		*/
		virtual const std::string& getName() const = 0;

		/**
		* @brief Function used to listen on a special port if needed by the module.
		* @details This function allows the module to specify to the server if
		* the module needs to listen on a specific port. The function pointer allows
		* the implementer to instantiate custom socket in its own network's logic 
		* implementation.
		* @param port the value of the port to be listened on. Default value
		* must be 80 when module do not need to listen on a specific port.
		* @return A function pointer which act as a socket builder functor taking
		* a file descriptor in argument and returning instantiated socket.
		*/
		virtual socketBuilder listen(unsigned short& port) const = 0;

		/**
		* @brief Getter for the module's priority
		* @details This method allows the implementor to retrieve the priority
		* of the module.
		* @return A float being the priority of the module. 
		*/
		virtual float getPriority() const = 0;

		/**
		* @brief Getter for the module's version
		* @details This method allows the implementor to retrieve the version
		* of the module.
		* @return A float being the version od the module.
		*/
		virtual float getVersion() const = 0;

		/**
		* @brief Getter for the module's type
		* @details This method allows the implementor to retrieve the module's
		* type.
		* @return The type of the module.
		*/
		virtual eModule getModuleType() const = 0;

		/**
		* @brief Getter for the module's logger
		* @details This method allows the implementor to retrieve the logger
		* stored in the module.
		* @return A reference to the logger.
		*/
		virtual ILogger* getLogger() = 0;

		/**
		* @brief Attach the module to a given execution process.
		* @details This method allows a module to attach itself to a given
		* execution process.
		* @param executionProcess The instance to which the module is going to
		* be attached to.
		* @return Itself
		*/
		virtual IModule& attachModule(IExecutionProcess* executionProcess) = 0;

		/**
		* @brief Detach the module to a given execution process.
		* @details This method allows a module to detach itself to a given
		* execution process.
		* @param executionProcess The instance from which the module is going to
		* be detached.
		* @return Itself
		*/
		virtual IModule& detachModule(IExecutionProcess* executionProcess) = 0;

		/**
		* @brief Sets the client in the module.
		* @details This method allows the implementor to set a given client in the
		* module. This way, it can handle the queries as it wants.
		* @param client The client to set in the module.
		* @return Itself
		*/
		virtual IModule& setClient(IClient* client) = 0;


		/**
		* @brief Function used to execute the module for a specific query.
		* @details This method allows the implementor to run a module for a
		* specific query. It can be used by the IExecutionProcess or by the Module
		* itself.
		* @param state The exepected module's state treatment level.
		* @param query The query for which the module is going to run.
		* @return The new query generated by the module.
		*/
		virtual IQuery* exec(eModule state, IQuery* query) = 0;

		/**
		* @brief Clones a module.
		* @details This method allows the implementor to clone the module
		* in order to retrieve a copy of it.
		* @return The cloned module.
		*/
		virtual IModule* clone() = 0;
	};
}