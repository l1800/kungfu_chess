#pragma once

#include "position.hpp"

class Motion
{
public:
    Motion(
        int pieceId,
        const Position& source,
        const Position& destination
    );

    int pieceId() const;

    const Position& source() const;
    const Position& destination() const;

    int elapsedMs() const;
    int durationMs() const;

    bool isComplete() const;

    void advance(int milliseconds);

private:
    static int calculateDurationMs(
        const Position& source,
        const Position& destination
    );

    int pieceId_;
    Position source_;
    Position destination_;

    int elapsedMs_;
    int durationMs_;
};