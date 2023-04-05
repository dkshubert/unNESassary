#pragma once

namespace unnes
{

/// @brief An interface representing a real world electronic device with which a user can interact.
/// For example, an NES or a Television.
struct IElectronicDevice {
    /// @brief Switches this device on.
    virtual void turnOn() = 0;

    /// @brief Switches this device off.
    virtual void turnOff() = 0;

    /// @returns True if this device is switched on, false otherwise.
    [[nodiscard]] virtual bool isOn() const = 0;

    /// @brief Implementers of this method calculate the time difference since the last call to
    /// update, and perform as many updates as is required to catch up to the current time. The
    /// number of updates to perform is a function of the different implementer's requirements:
    /// clock speed and refresh rate, as an example.
    ///
    /// @param time The time since application start (in seconds).
    /// @return True if the implementer has successfully updated, false otherwise.
    [[nodiscard]] virtual bool update(double time) = 0;
};

}  // namespace unnes
