/* 
  KDR Vario. Digital variometer based on Arduino.
  Copyright (C) 2011 Andrey Lebedev

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef filter_h
#define filter_h

class AlphaBetaFilter {
	private:
		float _alpha;
		float _beta;
		unsigned long _lastts;

		float _position;
		float _velocity;
		bool _initialized;

	public:
		AlphaBetaFilter(float alpha, float beta);
		void filter(long value);
		float getPosition();
		float getVelocity();
/**
 *  PCSLARA mods
 */
                float getAlpha() const;
                float getBeta() const;
                
                void setAlpha( float alpha );
                void setBeta( float beta );
};

#endif
