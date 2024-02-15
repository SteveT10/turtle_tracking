FROM node:16-alpine
# RUN mkdir /server
WORKDIR /server
COPY package-lock.json package.json ./
RUN npm ci
COPY . .
#CMD ["npm", "start"]